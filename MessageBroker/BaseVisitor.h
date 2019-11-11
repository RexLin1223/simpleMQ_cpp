#pragma once
#include "MessageBrokerDef.h"
#include <Common/Utility.h>

namespace message {
	// Forward declaration
	class Worker;
	class BaseRoom;

	class BaseVisitor : public std::enable_shared_from_this<BaseVisitor> {
	protected:
		VisitorInfo properties_;
		std::shared_ptr<Worker> worker_;

		BaseVisitor(
			VisitorInfo&& properties,
			std::shared_ptr<Worker> worker);
		virtual ~BaseVisitor();

		OnError on_error_;
		OnClose on_close_;

		void timer_worker();
		void send_alive();
	
		void start();
		void stop();
	public:
		void set_on_error(OnError&& on_error);
		void set_on_close(OnClose&& on_close);

		virtual void run() = 0;
		virtual void set_room(std::shared_ptr<BaseRoom> room) = 0;

		VisitorInfo::Type get_type();
		std::string get_category();
		std::string get_topic();
		std::string get_uid();
	};
}