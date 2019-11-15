#include "MessageSubscriber.h"
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

class DataHandler {
	queue::LockedList<std::string> list_;
	boost::asio::io_context io_context_;
	boost::asio::steady_timer timer_;
	boost::thread thread_;
public:
	DataHandler() 
		: io_context_()
		, timer_(io_context_)
	{
	}

	~DataHandler() {
		io_context_.stop();
		thread_.join();
	}

	void run() {
		count_list();
		thread_ = boost::thread([this]() {
			io_context_.run();
		});
	}

	void on_data(std::shared_ptr<std::string> data) {
		list_.push(*data);
	}

	void count_list() {
		timer_.expires_after(std::chrono::seconds(1));
		timer_.async_wait([this](boost::system::error_code ec) {
			if (ec) {
				logger::error("count_list", ec.message());
				return;
			}

			logger::info("count_list", list_.size());
			list_.consume_all();
			count_list();
		});
	}
};

bool is_running = false;
void on_error(const std::string& error_message) {
	is_running = false;
}

void main() {
	DataHandler handler;
	handler.run();

	auto subscriber = std::make_shared<message::Subscriber>("test", "test1");
	subscriber->set_on_data(std::bind(&DataHandler::on_data, &handler, std::placeholders::_1));
	subscriber->set_on_error(&on_error);
	
	is_running = true;
	subscriber->start("127.0.0.1", "53064");
	
	
	while (is_running) {
		boost::this_thread::sleep_for(boost::chrono::seconds(1));
	}
}