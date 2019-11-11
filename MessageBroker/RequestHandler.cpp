#include "RequestHandler.h"
#include <Common/MessageChannel.h>

#include "Sender.h"
#include "Receiver.h"

#include <ProtocolBuffers/message_dispatcher.h>
#include <ProtocolBuffers/message_deserializer.h>
#include <ProtocolBuffers/customized_message.pb.h>

namespace message {
	RequestHandler::RequestHandler(
		boost::asio::ip::tcp::socket&& socket, 
		std::shared_ptr<Worker> worker,
		OnVisitor on_visitor)
		: socket_(std::move(socket))
		, worker_(worker)
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
		read_header();
	}

	void RequestHandler::read_header()
	{
		auto self = shared_from_this();
		boost::asio::async_read(socket_, read_buffer_.prepare(8),
			[self, this](boost::system::error_code ec, std::size_t byte_transferred) {
			if (!ec) {
				read_buffer_.commit(byte_transferred);
				const char* data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
				if (data_ptr[0] == 0x00 && data_ptr[1] == 0x00 && data_ptr[2] == 0x01 && (unsigned char)data_ptr[3] == 0xb2) {
					uint32_t  payload_size;
					memcpy(&payload_size, data_ptr + 4, sizeof(uint32_t));
					if (payload_size > 0) {
						read_body(payload_size);
					}
				}
				read_buffer_.consume(byte_transferred);
			}
		});
	}

	void RequestHandler::read_body(size_t body_size)
	{
		auto self = shared_from_this();
		boost::asio::async_read(socket_, read_buffer_.prepare(body_size),
			[self, this](boost::system::error_code ec, std::size_t byte_transferred) {
			if (!ec) {
				read_buffer_.commit(byte_transferred);

				const char* data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
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

		auto sender = std::make_shared<Sender>(std::move(info), worker_);
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

		auto receiver = std::make_shared<Receiver>(std::move(info), worker_);
		if (receiver && on_visitor_) {
			on_visitor_(std::dynamic_pointer_cast<BaseVisitor>(receiver));
		}

	}
}