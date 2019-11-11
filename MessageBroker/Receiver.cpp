#include "Receiver.h"
#include "BaseRoom.h"
#include <Common/MessageChannel.h>

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
		bool is_writing = !queue_.empty();
		queue_.push(serializedMessage);
		if (!is_writing) {
			send();
		}
	}

	void Receiver::send()
	{
		if (queue_.empty()) {
			return;
		}

		auto data = queue_.fetch();
		boost::asio::async_write(properties_.socket_,
			boost::asio::buffer(
				data->data(),
				data->size()),
			[data, this]
		(boost::system::error_code ec,
			std::size_t byte_transferred) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message());
				}
			}

			if (queue_.size() > 0) {
				send();
			}
		});
	}
}