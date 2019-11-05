#pragma once
#include "MessageQueue.h"

namespace message {
	class BaseRoom {
	protected:
		std::string room_name_;
		MessageChannelPtr channel_;
		
		BaseRoom() = default;
		BaseRoom(const std::string& room_name);
		virtual ~BaseRoom();

		// Call by receiver
		void join(ChannelListener&& listener);
		void left(const std::string& listener_id);
	};
	
}