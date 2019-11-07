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
		
	public:
		MessageChannelPtr get_channel();
	};
	
}