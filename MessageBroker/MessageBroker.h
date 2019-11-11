#pragma once
#include <memory>
#include <string>
#include <Common/Worker.h>

namespace message {
	class RequestListener;
	class RoomManager;

	class BaseVisitor;

	class Broker {
		std::shared_ptr<Worker> worker_;

		std::unique_ptr<RequestListener> listener_;
		std::unique_ptr<RoomManager> room_manager_;
	public:
		Broker();
		virtual ~Broker();

		bool start();
		void stop();

	private:
		void on_visitor(std::shared_ptr<BaseVisitor> visitor);
	};
}