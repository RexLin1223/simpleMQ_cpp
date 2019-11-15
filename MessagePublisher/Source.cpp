#include "MessagePublisher.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

bool is_running = false;
void on_error(const std::string& error) {
	is_running = false;
}

void main() {
	auto pub = std::make_shared<message::Publisher>("test", "test1");
	pub->set_on_error(&on_error);
	pub->start("172.16.10.48", "53064");

	/*auto pub2 = std::make_shared<message::Publisher>("test", "test1");
	pub2->set_on_error(&on_error);
	pub2->start("127.0.0.1", "53064");*/
		
	is_running = true;
	while (is_running) {
		boost::this_thread::sleep_for(boost::chrono::milliseconds(0));
		pub->send("<Event> <DeviceID>0</DeviceID> <Type>ControlPortStart</Type> <LocalTime>1571369197655</LocalTime> <DeviceTime>1571369197655</DeviceTime> <Count>1</Count> <Status id=\"1\" trigger=\"1\" value=\"1\"/> </Event>");
		//pub2->send("<Event> <DeviceID>0</DeviceID> <Type>ControlPortStart</Type> <LocalTime>1571369197655</LocalTime> <DeviceTime>1571369197655</DeviceTime> <Count>1</Count> <Status id=\"1\" trigger=\"1\" value=\"1\"/> </Event>");
	}
}