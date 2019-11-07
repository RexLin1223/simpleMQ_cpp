#pragma once
#include <memory>
#include <string>

namespace message {
	class RequestListener;
	class RoomManager;

	class BaseVisitor;

	class Broker {
		std::unique_ptr<RequestListener> listener_;
		std::unique_ptr<RoomManager> room_manager_;
	public:
		Broker();
		virtual ~Broker();

		bool strart();
		void stop();

	private:
		void on_visitor(std::shared_ptr<BaseVisitor> visitor);
	};
}