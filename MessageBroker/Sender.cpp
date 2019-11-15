#include "Sender.h"
#include "BaseRoom.h"

#include <Common/logger.h>

#include <ProtocolBuffers/message_deserializer.h>
#include <ProtocolBuffers/message_serializer.h>
#include <ProtocolBuffers/message_dispatcher.h>
#include <ProtocolBuffers/customized_message.pb.h>
namespace message {

	Sender::Sender(VisitorInfo&& properties, std::shared_ptr<Worker> worker)
		: BaseVisitor(std::move(properties), worker)
		, message_dispatcher_(std::make_shared<proto::message_dispatcher>())
		, room_(nullptr)
		, channel_(nullptr)
	{
		message_dispatcher_->register_handler<PublisherMessage>(
			std::bind(&Sender::on_message, this, std::placeholders::_1));
	}

	Sender::~Sender()
	{
		stop();
	}

	void Sender::run()
	{
		read_header();
		BaseVisitor::start();
	}

	void Sender::close()
	{
		BaseVisitor::stop();

		if (on_close_) {
			on_close_();
		}
	}

	void Sender::set_room(std::shared_ptr<BaseRoom> room) {
		room_ = room;
		channel_ = room->get_channel();
	}

	void Sender::read_header()
	{
		auto self = shared_from_this();
		boost::asio::async_read(properties_.socket_, read_buffer_.prepare(8),
			[self, this](
				boost::system::error_code ec, 
				std::size_t transferred_bytes) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				close();
				return;
			}
			//logger::debug("Sender", "read_header");

			read_buffer_.commit(transferred_bytes);
			std::string data(boost::asio::buffer_cast<const char*>(read_buffer_.data()), transferred_bytes);
			read_buffer_.consume(transferred_bytes);

			const char* data_ptr = data.c_str();
			if (check_start_code(data_ptr)) {
				uint32_t  payload_size;
				memcpy(&payload_size, data_ptr + 4, sizeof(uint32_t));
				if (payload_size > 0) {
					read_body(payload_size);
				}
				else {
					logger::error("Sender", "invalid payload length");
					read_header();
				}
			}
			else {
				logger::error("Sender", "error_header");
				read_header();
			}
		});
	}

	void Sender::read_body(uint32_t body_size)
	{
		auto self = shared_from_this();
		boost::asio::async_read(properties_.socket_, read_buffer_.prepare(body_size),
			[self, this](boost::system::error_code ec, std::size_t byte_transferred) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				close();
				return;
			}
			//logger::debug("Sender", "read_body");

			read_buffer_.commit(byte_transferred);
			std::string data(boost::asio::buffer_cast<const char*>(read_buffer_.data()), byte_transferred);
			read_buffer_.consume(byte_transferred);

			if (message_dispatcher_) {
				message_dispatcher_->dispatch(
					proto::message_deserializer::deserialize(
						data.c_str(), data.size()));
			}

			read_header();
		});
	}

	void Sender::on_message(const std::shared_ptr<PublisherMessage> message)
	{
		std::string serialized = proto::message_serializer::serialize(*message);
		if (channel_) {
			channel_->broadcast(serialized);
		}
	}
}

