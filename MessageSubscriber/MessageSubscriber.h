#pragma once
#include <Common/LockedContainer.h>
#include <Common/Logger.h>
#include <Common/Worker.h>
#include <Common/Utility.h>

namespace message  {

	class Subscriber : public Worker, public std::enable_shared_from_this<Subscriber> {
		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf read_buffer_;
		queue::LockedLinkList<std::shared_ptr<std::string>> list_;

		std::string sub_category_;
		std::string sub_topic_;

		OnData on_data_;
	public:
		Subscriber() = delete;
		Subscriber(const std::string& category, const std::string& topic)
			: Worker(1)
			, resolver_(boost::asio::make_strand(io_context_))
			, socket_(io_context_)
			, sub_category_(category)
			, sub_topic_(topic)
		{}

		void start(const std::string& host, const std::string& port) {
			do_resolve(host, port);
			Worker::run();
		}

		void stop() {
			boost::system::error_code ec;
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
			socket_.close(ec);
		}

		void set_on_data(OnData on_data) {
			on_data_ = on_data;
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
			auto timer = std::make_shared<boost::asio::steady_timer>(io_context_);
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
				do_receive();
			});
		}
		void do_receive() {
			auto self = shared_from_this();
			boost::asio::async_read(
				socket_, read_buffer_,
				[self, this] (
					boost::system::error_code ec, 
					std::size_t bytes_transfered) {
				read_buffer_.commit(bytes_transfered);
				if (ec) {
					logger::error("receive", ec.message());
					return;
				}

				// Get data from buffer
				const char *data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
				list_.push(std::make_shared<std::string>(data_ptr, bytes_transfered));
				read_buffer_.consume(bytes_transfered);

				do_receive();
			});
		}
	};
}