#pragma once
#include "Worker.h"
#include <boost/asio.hpp>

namespace message {
	class RequestListener : public Worker {
		std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;

	public:
		RequestListener();
		virtual ~RequestListener();

		bool start(unsigned short port);
		void stop();

	private:
		void do_accept();
	};
}