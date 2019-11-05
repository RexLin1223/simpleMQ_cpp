#include "BaseVisitor.h"

namespace message {

	BaseVisitor::BaseVisitor(VisitorProperties&& properties)
		: Worker(1)
		, properties_(std::move(properties))
	{
		send_alive();
	}

	BaseVisitor::~BaseVisitor()
	{
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

	void BaseVisitor::timer_worker()
	{
		auto self = shared_from_this();
		timer_.expires_after(std::chrono::seconds(5));
		timer_.async_wait([this, self](boost::system::error_code ec) {
			if (ec) {
				return;
			}

			// Execute worker
			send_alive();

			timer_worker();
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
				timer_.cancel();
			}
		});
	
		
	}

}