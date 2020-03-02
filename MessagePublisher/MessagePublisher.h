#pragma once
#include <Common/LockedContainer.h>
#include <Common/Logger.h>
#include <Common/Worker.h>
#include <Common/Utility.h>

#include <ProtocolBuffers/message_serializer.h>
#include <ProtocolBuffers/customized_message.pb.h>

namespace message {
	class Publisher : public std::enable_shared_from_this<Publisher> {
		Worker worker_;

		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ip::tcp::socket socket_;

		queue::LockedList<std::shared_ptr<std::string>> list_;
		message::PublisherMessage message_;

		boost::shared_mutex mutex_;

		OnError on_error_;
	public:
		Publisher() = delete;
		Publisher(const std::string& category, const std::string& topic)
			: worker_(1)
			, resolver_(boost::asio::make_strand(worker_.io_context_))
			, socket_(worker_.io_context_)
		{
			auto properties =  message_.mutable_properties();
			properties->set_type(VisitorType::publisher);
			properties->set_category(category);
			properties->set_topic(topic);
		}

		void start(const std::string& host, const std::string& port) {
			do_resolve(host, port);
			worker_.run();
		}

		void stop() {
			boost::system::error_code ec;
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
			socket_.close(ec);

			worker_.stop();
		}

		void send(const std::string& data) {
			message_.set_payload(data);

			auto data_ptr = std::make_shared<std::string>(
				proto::message_serializer::serialize(message_));
			list_.push(data_ptr);

			auto self = shared_from_this();
			worker_.io_context_.post([self, this]() {
				do_send();
			});
		}

		void send(std::string&& data) {
			message_.set_payload(std::move(data));

			auto data_ptr = std::make_shared<std::string>(
				proto::message_serializer::serialize(message_));

			bool need_to_send = false;
			{
				boost::unique_lock<boost::shared_mutex> lock(mutex_);
				need_to_send = list_.empty();
				list_.push(data_ptr);
			}

			if (need_to_send) {
				worker_.io_context_.post([this]() {
					do_send();
				});
			}
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
			
			std::shared_ptr<std::string> data_ptr = nullptr;
			{
				boost::unique_lock<boost::shared_mutex> lock(mutex_);
				if (list_.empty()) return;
				data_ptr = list_.peek();
				if (!data_ptr) return;
			}

			auto buf_vec_ptr = std::make_shared<std::vector<boost::asio::const_buffer>>();
			uint32_t size = data_ptr->size(); 
			buf_vec_ptr->emplace_back(boost::asio::buffer(start_code, sizeof(start_code)));
			buf_vec_ptr->emplace_back(boost::asio::buffer(&size, sizeof(uint32_t)));
			buf_vec_ptr->emplace_back(boost::asio::buffer(*data_ptr));
			
			auto self = shared_from_this();
			boost::asio::async_write(
				socket_, *buf_vec_ptr,
				[this, self, buf_vec_ptr](
					boost::system::error_code ec,
					std::size_t bytes_transfered) {
				if (ec) {
					logger::error("write", ec.message());
					if (on_error_) {
						on_error_(ec.message());
					}
					return;
				}

				bool need_send_next = false;
				{
					boost::unique_lock<boost::shared_mutex> lock(mutex_);
					//logger::debug("Publisher", ++count);
					list_.consume_one();
					need_send_next = !list_.empty();
				}

				if (need_send_next) {
					do_send();
				}
			});
		}
	};
}