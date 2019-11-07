#pragma once
#include <Common/LockedContainer.h>
#include <Common/Logger.h>
#include <Common/Worker.h>
#include <Common/Utility.h>

namespace message {

	class Publisher : public Worker, public std::enable_shared_from_this<Publisher> {
		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ip::tcp::socket socket_;
		queue::LockedLinkList<std::shared_ptr<std::string>> list_;

		std::string sub_category_;
		std::string sub_topic_;
	public:
		Publisher() = delete;
		Publisher(const std::string& category, const std::string& topic)
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

		void send(const std::string& data) {
			auto data_ptr = std::make_shared<std::string>(data);
			list_.push(data_ptr);

			auto self = shared_from_this();
			io_context_.post([self, this]() {
				do_send();
			});
		}

		void send(std::string&& data) {
			auto data_ptr = std::make_shared<std::string>(std::move(data));
			list_.push(data_ptr);

			auto self = shared_from_this();
			io_context_.post([this]() {
				do_send();
			});
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
				do_send();
			});
		}
		void do_send() {
			if (list_.empty()) return;

			auto data_ptr = list_.fetch();
			auto self = shared_from_this();
			boost::asio::async_write(
				socket_, boost::asio::buffer(*data_ptr),
				[data_ptr, self, this](
					boost::system::error_code ec,
					std::size_t bytes_transfered) {
				if (ec) {
					logger::error("write", ec.message());
					return;
				}

				if (!list_.empty()) {
					do_send();
				}
			});
		}
	};
}