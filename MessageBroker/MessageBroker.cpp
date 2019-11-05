#include "MessageBroker.h"
#include "RoomManager.h"
#include "RequestListener.h"

// Visitor
#include "Sender.h"
#include "Receiver.h"

namespace message {

	Broker::Broker()
		: listener_(new RequestListener)
		, room_manager_(new RoomManager)
	{

	}

	Broker::~Broker()
	{

	}

	void Broker::on_visitor(std::string&& data) {
		// Get room
		if (!room_manager_)  return;

		std::string room_name; // TODO
		auto channel = room_manager_->get_room_channel(room_name);

		VisitorProperties properties;
		// Join room
		std::string visitor_type = "sender";

		std::shared_ptr<BaseVisitor> visitor = nullptr;
		if ("sender"==visitor_type) {
			visitor = std::make_shared<Sender>(std::move(properties));
		}
		else if ("receiver" == visitor_type) {
			visitor = std::make_shared<Receiver>(std::move(properties));
		}

		// Start visitor
		if (visitor) {
			visitor->set_on_error([this](const std::string& error_message) {
				printf("Error=%s\n", error_message.c_str());
			});

			visitor->set_on_close([]() {
				printf("Close\n");
			});

			visitor->start();
		}

	}

}