#pragma once
#include "BaseVisitor.h"
#include <Common/LockedContainer.h>

namespace message {
	class BaseRoom;

	class Receiver : public BaseVisitor {
		queue::LockedList<std::shared_ptr<std::string>> queue_;
		std::shared_ptr<BaseRoom> room_;

		boost::shared_mutex mutex_;
	public:
		Receiver(VisitorInfo&& properties, 
			std::shared_ptr<Worker> worker);
		virtual ~Receiver();

		void run() override;
		void close() override;
		void set_room(std::shared_ptr<BaseRoom> room) override;

	private:
		void on_message(std::shared_ptr<std::string> message);
		void send();
	};
}