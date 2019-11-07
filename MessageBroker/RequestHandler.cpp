#include "RequestHandler.h"
#include "MessageChannel.h"

#include "Sender.h"
#include "Receiver.h"

#include <ProtocolBuffers/message_dispatcher.h>
#include <ProtocolBuffers/message_deserializer.h>
#include <ProtocolBuffers/customized_message.pb.h>

namespace message {
	RequestHandler::RequestHandler(
		boost::asio::ip::tcp::socket&& socket, 
		OnVisitor on_visitor)
		: socket_(std::move(socket))
		, on_visitor_(on_visitor)
		, message_dispatcher_(std::make_shared<proto::message_dispatcher>())
	{
		message_dispatcher_->register_handler<PublisherMessage>(
			std::bind(&RequestHandler::on_publisher,
				this, std::placeholders::_1));

		message_dispatcher_->register_handler<SubscriberMessage>(
			std::bind(&RequestHandler::on_subscriber,
				this, std::placeholders::_1));
	}

	RequestHandler::~RequestHandler()
	{
		
	}

	void RequestHandler::run()
	{
		auto self = shared_from_this();
		boost::asio::async_read(socket_, read_buffer_.prepare(64),
			[self, this](boost::system::error_code ec, std::size_t byte_transferred) {
			if (!ec) {
				read_buffer_.commit(byte_transferred);

				const char *data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
				
				if (message_dispatcher_) {
					message_dispatcher_->dispatch(
						proto::message_deserializer::deserialize(
							data_ptr, byte_transferred));
				}

				read_buffer_.consume(byte_transferred);
			}
		});
	}

	void RequestHandler::on_publisher(const std::shared_ptr<PublisherMessage> pubMessage)
	{
		const VisitorProperty& properties = pubMessage->properties();
		VisitorInfo info(
			std::move(socket_),
			properties.category(),
			properties.topic(),
			get_uuid(),
			VisitorInfo::Type::Publisher);

		auto sender = std::make_shared<Sender>(std::move(info));
		if (sender && on_visitor_) {
			on_visitor_(std::dynamic_pointer_cast<BaseVisitor>(sender));
		}
	}

	void RequestHandler::on_subscriber(const std::shared_ptr<SubscriberMessage> subMessage)
	{
		const VisitorProperty& properties = subMessage->properties();
		VisitorInfo info(
			std::move(socket_),
			properties.category(),
			properties.topic(),
			get_uuid(),
			VisitorInfo::Type::Subscriber);

		auto receiver = std::make_shared<Receiver>(std::move(info));
		if (receiver && on_visitor_) {
			on_visitor_(std::dynamic_pointer_cast<BaseVisitor>(receiver));
		}

	}
}