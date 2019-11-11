#include "Sender.h"
#include "BaseRoom.h"

#include <Common/MessageChannel.h>
#include <Common/logger.h>

#include <ProtocolBuffers/message_deserializer.h>
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

	void Sender::set_room(std::shared_ptr<BaseRoom> room) {
		room_ = room;
		channel_ = room->get_channel();
	}

	void Sender::read_header()
	{
		auto self = shared_from_this();
		boost::asio::async_read(properties_.socket_, read_buffer_.prepare(8),
			[self, this](boost::system::error_code ec, std::size_t transferred_bytes) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				if (on_close_) {
					on_close_();
				}
				return;
			}

			read_buffer_.commit(transferred_bytes);
			const char* data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
			if (data_ptr[0] == 0x00 && data_ptr[1] == 0x00 && data_ptr[2] == 0x01 && (unsigned char)data_ptr[3] == 0xb2) {
				uint32_t  payload_size;
				memcpy(&payload_size, data_ptr + 4, sizeof(uint32_t));
				if (payload_size > 0) {
					read_body(payload_size);
				}
			}
			read_buffer_.consume(transferred_bytes);
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
				if (on_close_) {
					on_close_();
				}
				return;
			}
			read_buffer_.commit(byte_transferred);
			const char* data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
			if (message_dispatcher_) {
				message_dispatcher_->dispatch(
					proto::message_deserializer::deserialize(
						data_ptr, byte_transferred));
			}

			read_buffer_.consume(byte_transferred);
			read_header();
		});
	}

	void Sender::on_message(const std::shared_ptr<PublisherMessage> message)
	{
		const std::string& payload = message->payload();
		logger::debug("Sender", properties_.unique_id_ + " " + payload);
		if (channel_) {
			channel_->broadcast(payload);
		}
	}
}

