#include "MessageSubscriber.h"
#include <iostream>

void main() {
	auto subscriber = std::make_shared<message::Subscriber>("test", "event");
	subscriber->set_on_data([](std::shared_ptr<std::string> data) {
		logger::debug("callback", data);
	});
	subscriber->start("127.0.0.1", "53064");

	int t;
	std::cin >> t;
}