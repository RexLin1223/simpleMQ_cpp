#include "MessageBroker.h"
#include "RoomManager.h"
#include "RequestListener.h"

// Visitor
#include "Sender.h"
#include "Receiver.h"

// Proto buffer
#include <ProtocolBuffers/customized_message.pb.h>

namespace message {

	Broker::Broker()
		: listener_(std::make_unique<RequestListener>())
		, room_manager_(std::make_unique<RoomManager>())
	{
	}

	Broker::~Broker()
	{
		listener_.reset();
		room_manager_.reset();
	}

	bool Broker::strart()
	{
		if (!room_manager_ || !listener_ || !listener_->start(53064)) {
			return false;
		}

		listener_->set_on_visitor(std::bind(&Broker::on_visitor, this, std::placeholders::_1));
		return true;
	}

	void Broker::stop()
	{
		if (listener_) {
			listener_->stop();
		}
	}

	void Broker::on_visitor(std::shared_ptr<BaseVisitor> visitor)
	{
		if (!room_manager_) return;
		auto channel = room_manager_->get_room_channel(visitor->get_category(), visitor->get_topic());
		if (!channel) return;
		
		visitor->set_on_error([this](const std::string& error_message) {
			printf("Error=%s\n", error_message.c_str());
		});

		visitor->set_on_close([this]() {
			printf("Close\n");
		});

		visitor->set_channel(channel);
		visitor->run();
	}
}