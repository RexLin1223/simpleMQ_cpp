#pragma once
#include <string>
#include <memory>
#include <boost/asio.hpp>

namespace message {
	class RequestHandler : public std::enable_shared_from_this<RequestHandler> {
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf read_buffer_;
		OnVisitor on_visitor_;
	public:
		RequestHandler(boost::asio::ip::tcp::socket socket);
		virtual ~RequestHandler();

		void run();
		void set_hanlder(OnVisitor on_visitor);
	};
}