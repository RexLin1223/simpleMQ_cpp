#include "MessageBroker.h"
#include "RoomManager.h"
#include "RequestListener.h"

// Visitor
#include "Sender.h"
#include "Receiver.h"

// Proto buffer
#include <ProtocolBuffers/customized_message.pb.h>

#include <Common/logger.h>

namespace message {

	Broker::Broker()
		: worker_(std::make_shared<Worker>(2))
		, listener_(std::make_unique<RequestListener>(worker_))
		, room_manager_(std::make_unique<RoomManager>())
	{
	}

	Broker::~Broker()
	{
		listener_.reset();
		room_manager_.reset();
	}

	bool Broker::start()
	{
		if (!worker_ || !listener_ || !room_manager_) {
			return false;
		}
		listener_->start(53064);
		worker_->run();

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
		auto room_ptr = room_manager_->get_room(visitor->get_category(), visitor->get_topic());
		if (!room_ptr) return;
		
		visitor->set_on_error([this](const std::string& error_message) {
			logger::error("on_visitor", error_message.c_str()); 
		});

		visitor->set_on_close([this]() {
			logger::info("on_visitor", "close");
		});

		visitor->set_room(room_ptr);
		visitor->run();
	}
}