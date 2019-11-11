#include "MessageBroker.h"
#include <iostream>

int main() {
	message::Broker broker;
	broker.start();

	int i;
	std::cin >> i;
}