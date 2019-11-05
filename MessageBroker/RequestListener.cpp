#include "RequestListener.h"
#include "RequestHandler.h"

namespace message {

	RequestListener::RequestListener()
		: Worker(1)
		, acceptor_(nullptr)
	{
	}

	RequestListener::~RequestListener()
	{
	}

	bool RequestListener::start(unsigned short port)
	{
		acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(
			io_context_, boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port));
		if (!acceptor_) return false;

		do_accept();
		Worker::run();
		return true;
	}

	void RequestListener::stop()
	{
		Worker::stop();
	}

	void RequestListener::do_accept()
	{
		acceptor_->async_accept(
			[this](boost::system::error_code ec, 
				boost::asio::ip::tcp::socket socket) {
			if (!ec) {
				std::make_shared<RequestHandler>(std::move(socket))->run();
			}

			do_accept();
		});
	}
}