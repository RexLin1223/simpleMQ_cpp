#include "RequestListener.h"
#include "RequestHandler.h"

#include <iostream>

#include <Common/logger.h>
#include <boost/format.hpp>

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
		try {
			acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(
				io_context_, boost::asio::ip::tcp::endpoint(
					boost::asio::ip::tcp::v4(), port));
			if (!acceptor_) return false;

			do_accept();
			Worker::run();

			logger::info("start", boost::str(boost::format("Listening port: %s") % port));
			return true;
		}
		catch (std::exception ex) {
			logger::error("start", ex.what());
		}
		return false;
	}

	void RequestListener::stop()
	{
		Worker::stop();
	}

	void RequestListener::set_on_visitor(OnVisitor on_visitor)
	{
		on_visitor_ = on_visitor;
	}

	void RequestListener::do_accept()
	{
		acceptor_->async_accept(
			[this](boost::system::error_code ec, 
				boost::asio::ip::tcp::socket socket) {
			if (ec) {
				logger::error("accept", ec.message());
				return;
			}

			logger::info("accept", "New visitor coming!");
			std::make_shared<RequestHandler>(
				std::move(socket), on_visitor_)->run();

			do_accept();
		});
	}

}