#include "MessagePublisher.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

void main() {
	auto pub = std::make_shared<message::Publisher>("test", "test1");
	pub->start("127.0.0.1", "53064");
	while (1) {
		boost::this_thread::sleep_for(boost::chrono::seconds(1));
		pub->send("30643064306430643064306430643064");
	}
}