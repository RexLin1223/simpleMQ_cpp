#pragma once
#include <memory>
#include <string>

namespace message {
	class RequestListener;
	class RoomManager;

	class Broker {
		std::unique_ptr<RequestListener> listener_;
		std::unique_ptr<RoomManager> room_manager_;

	public:
		Broker();
		virtual ~Broker();

	private:
		void on_visitor(std::string&& data);
	};
}