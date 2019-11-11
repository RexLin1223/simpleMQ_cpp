#include "BaseVisitor.h"
#include <Common/Worker.h>

namespace message {

	BaseVisitor::BaseVisitor(
		VisitorInfo&& properties,
		std::shared_ptr<Worker> worker)
		: properties_(std::move(properties))
		, worker_(worker)
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
		worker_->timer_.cancel();
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
		worker_->timer_.expires_after(std::chrono::seconds(5));
		worker_->timer_.async_wait([this, self](boost::system::error_code ec) {
			if (ec) {
				return;
			}

			send_alive();
		});
	}

	void BaseVisitor::send_alive()
	{
		auto self = shared_from_this();
		boost::asio::async_write(properties_.socket_, 
			boost::asio::buffer("keep_alive"),
			[this, self](boost::system::error_code ec, std::size_t byte_transferred) {
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