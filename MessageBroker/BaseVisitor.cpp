#include "BaseVisitor.h"
#include <Common/Worker.h>
#include <Common/Logger.h>

#include <vector>

namespace message {

	BaseVisitor::BaseVisitor(
		VisitorInfo&& properties,
		std::shared_ptr<Worker> worker)
		: properties_(std::move(properties))
		, worker_(worker)
		, timer_(worker_->io_context_)
	{
	}

	BaseVisitor::~BaseVisitor()
	{
		stop();

		boost::system::error_code ec;
		properties_.socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		properties_.socket_.close(ec);
	}

	void BaseVisitor::set_on_error(OnError&& on_error)
	{
		on_error_ = on_error;
	}

	void BaseVisitor::set_on_close(OnClose&& on_close)
	{
		on_close_ = on_close;
	}

	void BaseVisitor::start()
	{
		timer_worker();
	}

	void BaseVisitor::stop()
	{
		timer_.cancel();
	}
	
	VisitorInfo::Type BaseVisitor::get_type()
	{
		return properties_.type_;
	}

	std::string BaseVisitor::get_category()
	{
		return properties_.category_;
	}

	std::string BaseVisitor::get_topic()
	{
		return properties_.topic_;
	}

	std::string BaseVisitor::get_uid()
	{
		return properties_.unique_id_;
	}

	void BaseVisitor::timer_worker()
	{
		auto self = shared_from_this();
		timer_.expires_after(std::chrono::seconds(5));
		timer_.async_wait([this, self](boost::system::error_code ec) {
			if (ec) {
				logger::error("timer worker", ec.message());
				return;
			}
			send_alive();
		});
	}

	void BaseVisitor::send_alive()
	{
		static auto keep_alive_message = std::make_shared<std::string>("keep_alive");
		std::shared_ptr<std::vector<boost::asio::const_buffer>> buf_vec_ptr =
			std::make_shared<std::vector<boost::asio::const_buffer>>();

		uint32_t size = keep_alive_message->size();
		buf_vec_ptr->emplace_back(boost::asio::buffer(start_code, sizeof(start_code)));
		buf_vec_ptr->emplace_back(boost::asio::buffer(&size, sizeof(uint32_t)));
		buf_vec_ptr->emplace_back(boost::asio::buffer(*keep_alive_message));
		
		auto self = shared_from_this();
		do_write(buf_vec_ptr, [this, self, buf_vec_ptr](boost::system::error_code ec, std::size_t byte_transferred) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				if (on_close_) {
					on_close_();
				}
				return;
			}

			timer_worker();
		});
	}

}