#pragma once
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <Common/Utility.h>
#include "MessageBrokerDef.h"

namespace proto {
	class message_dispatcher;
}

namespace message {
	class PublisherMessage;
	class SubscriberMessage;

	class RequestHandler : public std::enable_shared_from_this<RequestHandler> {
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf read_buffer_;

		std::shared_ptr<proto::message_dispatcher> message_dispatcher_;
		
		OnVisitor on_visitor_;
	public:
		RequestHandler() = delete;
		RequestHandler(
			boost::asio::ip::tcp::socket&& socket,
			OnVisitor on_visitor);
		virtual ~RequestHandler();

		void run();

		void on_publisher(const std::shared_ptr<PublisherMessage> pubMessage);
		void on_subscriber(const std::shared_ptr<SubscriberMessage> subMessage);
	};
}