#pragma once
#include <Common/LockedContainer.h>
#include <Common/Logger.h>
#include <Common/Worker.h>
#include <Common/Utility.h>

#include <ProtocolBuffers/message_deserializer.h>
#include <ProtocolBuffers/message_serializer.h>
#include <ProtocolBuffers/message_dispatcher.h>
#include <ProtocolBuffers/customized_message.pb.h>

namespace message  {

	class Subscriber : public std::enable_shared_from_this<Subscriber> {
		Worker worker_;

		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf read_buffer_;
		queue::LockedList<std::shared_ptr<std::string>> list_;

		proto::message_dispatcher message_dispatcher_;

		std::string sub_category_;
		std::string sub_topic_;

		OnData on_data_;
		OnError on_error_;
	public:
		Subscriber() = delete;
		Subscriber(const std::string& category, const std::string& topic)
			: worker_(1)
			, resolver_(boost::asio::make_strand(worker_.io_context_))
			, socket_(worker_.io_context_)
			, sub_category_(category)
			, sub_topic_(topic)
		{
			message_dispatcher_.register_handler<PublisherMessage>(
				std::bind(&Subscriber::on_message, 
					this, std::placeholders::_1));
		}

		void start(const std::string& host, const std::string& port) {
			do_resolve(host, port);
			worker_.run();
		}

		void stop() {
			boost::system::error_code ec;
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
			socket_.close(ec);
		}

		void set_on_data(OnData on_data) {
			on_data_ = on_data;
		}

		void set_on_error(OnError on_error) {
			on_error_ = on_error;
		}

	private:
		void do_resolve(const std::string& host, const std::string& port) {
			auto self = shared_from_this();
			resolver_.async_resolve(host, port,
				[self, this](boost::system::error_code ec,
					boost::asio::ip::tcp::resolver::results_type results) {
				if (ec) {
					logger::error("resolve", ec.message());
					return;
				}
				do_connect(results);
			});
		}

		void do_connect(boost::asio::ip::tcp::resolver::results_type results) {
			// Set timeout timer
			auto timer = std::make_shared<boost::asio::steady_timer>(worker_.io_context_);
			timer->expires_after(std::chrono::seconds(15));
			timer->async_wait([this](boost::system::error_code ec) {
				if (!ec) {
					// Timeout
					stop();
				}
			});

			auto self = shared_from_this();
			boost::asio::async_connect(socket_,
				results.begin(), results.end(),
				[self, timer, this](
					boost::system::error_code ec,
					boost::asio::ip::tcp::resolver::iterator it) {
				if (ec) {
					logger::error("connect", ec.message());
					return;
				}
				timer->cancel();
				do_send();
			});
		}

		void do_send() {
			SubscriberMessage message;
			auto properties = message.mutable_properties();
			properties->set_type(VisitorType::subscriber);
			properties->set_category(sub_category_);
			properties->set_topic(sub_topic_);

			std::string serialized = proto::message_serializer::serialize(message);
			auto data_ptr = std::make_shared<std::string>(std::move(serialized));

			std::vector<boost::asio::const_buffer> buf_vec;
			uint32_t size = data_ptr->size();
			buf_vec.emplace_back(boost::asio::buffer(start_code, sizeof(start_code)));
			buf_vec.emplace_back(boost::asio::buffer(&size, sizeof(uint32_t)));
			buf_vec.emplace_back(boost::asio::buffer(*data_ptr));

			auto self = shared_from_this();
			boost::asio::async_write(
				socket_, buf_vec,
				[data_ptr, self, this](
					boost::system::error_code ec,
					std::size_t bytes_transfered) {
				if (ec) {
					logger::error("write", ec.message());
					if (on_error_) {
						on_error_(ec.message());
					}
					return;
				}

				read_header();
			});

		}

		void read_header() {
			auto self = shared_from_this();
			boost::asio::async_read(
				socket_, read_buffer_.prepare(8),
				[self, this] (
					boost::system::error_code ec, 
					std::size_t bytes_transferred) {
				if (ec) {
					logger::error("read_header", ec.message());
					if (on_error_) {
						on_error_(ec.message());
					}
					return;
				}

				read_buffer_.commit(bytes_transferred);
				std::string data(boost::asio::buffer_cast<const char*>(read_buffer_.data()), bytes_transferred);
				read_buffer_.consume(bytes_transferred);

				const char* data_ptr = data.c_str();
				if (check_start_code(data_ptr)) {
					uint32_t  payload_size;
					memcpy(&payload_size, data_ptr + 4, sizeof(uint32_t));
					if (payload_size > 0) {
						read_body(payload_size);
					}
					else {
						logger::error("Sender", "invalid payload");
						read_header();
					}
				}
				else {
					logger::error("Sender", "error_header");
					read_header();
				}
			});
		}

		void read_body(uint32_t body_size) {
			auto self = shared_from_this();
			boost::asio::async_read(
				socket_, read_buffer_.prepare(body_size),
				[self, this](
					boost::system::error_code ec,
					std::size_t bytes_transferred) {
				if (ec) {
					logger::error("read_header", ec.message());
					if (on_error_) {
						on_error_(ec.message());
					}
					return;
				}

				read_buffer_.commit(bytes_transferred);
				const char* data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
				message_dispatcher_.dispatch(
					proto::message_deserializer::deserialize(
						data_ptr, bytes_transferred));

				read_buffer_.consume(bytes_transferred);
				read_header();
			});
		}

		void on_message(const std::shared_ptr<PublisherMessage> message) {
			if (on_data_) {
				on_data_(std::make_shared<std::string>(message->payload()));
			}
		}

	};
}