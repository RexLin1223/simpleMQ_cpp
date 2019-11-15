#include "Receiver.h"
#include "BaseRoom.h"
#include <Common/MessageChannel.h>
#include <Common/Worker.h>
#include <Common/Logger.h>

namespace message {

	Receiver::Receiver(
		VisitorInfo&& properties, 
		std::shared_ptr<Worker> worker)
		: BaseVisitor(std::move(properties), worker)
	{
	}

	Receiver::~Receiver()
	{
		stop();
	}

	void Receiver::run()
	{
		BaseVisitor::start();
	}

	void Receiver::set_room(std::shared_ptr<BaseRoom> room)
	{
		room_ = room;
		auto channel = room_->get_channel();
		if (channel) {
			channel->subscribe(properties_.unique_id_,
				std::bind(&Receiver::on_message, this, std::placeholders::_1));
		}
	}

	void Receiver::on_message(std::shared_ptr<std::string> serializedMessage)
	{
		bool need_to_send = false;
		{
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			need_to_send = queue_.empty();
			queue_.push(serializedMessage);
		}

		if (need_to_send) {
			send();
		}
	}

	void Receiver::send()
	{
		//logger::debug("Receiver", "send");

		std::shared_ptr<std::string> data_ptr;
		{
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			if (queue_.empty()) {
				return;
			}
			data_ptr = queue_.peek();
			if (!data_ptr) return;
		}
		auto buf_vec_ptr = std::make_shared<std::vector<boost::asio::const_buffer>>();
		uint32_t size = data_ptr->size();
		buf_vec_ptr->emplace_back(boost::asio::buffer(start_code, sizeof(start_code)));
		buf_vec_ptr->emplace_back(boost::asio::buffer(&size, sizeof(uint32_t)));
		buf_vec_ptr->emplace_back(boost::asio::buffer(*data_ptr));

		//logger::debug("Receiver", "write");
		auto self = shared_from_this();
		do_write(buf_vec_ptr, [this, self, buf_vec_ptr]
		(boost::system::error_code ec,
			std::size_t byte_transferred) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message());
				}
				close();
				return;
			}
			
			//logger::debug("Receiver", "on_write");
			bool need_send_next = false;
			{
				boost::unique_lock<boost::shared_mutex> lock(mutex_);
				queue_.consume_one();
				need_send_next = !queue_.empty();
			}

			if (need_send_next) {
				send();
			}
		});
	}

	void Receiver::close()
	{
		auto channel = room_->get_channel();
		if (channel) {
			channel->unsubscribe(properties_.unique_id_);
		}
		{
			boost::unique_lock<boost::shared_mutex> lock(mutex_);
			queue_.consume_all();
		}
		BaseVisitor::stop();

		if (on_close_) {
			on_close_();
		}
	}

}