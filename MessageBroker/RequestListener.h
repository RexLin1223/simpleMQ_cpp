#pragma once
#include "MessageBrokerDef.h"
#include <Common/Utility.h>
#include <Common/Worker.h>

#include <boost/asio.hpp>

namespace proto {
	class message_dispatcher;
}

namespace message {
	class PublisherMessage;
	class SubscriberMessage;
	class Worker;

	class RequestListener {
		std::shared_ptr<Worker> worker_;
		std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
		OnVisitor on_visitor_;
	public:
		RequestListener(std::shared_ptr<Worker> worker);
		virtual ~RequestListener();

		bool start(unsigned short port);
		void stop();

		void set_on_visitor(OnVisitor on_visitor);
	private:
		void do_accept();
	};
}