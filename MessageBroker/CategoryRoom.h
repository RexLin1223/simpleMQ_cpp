#pragma once
#include <string>
#include "BaseRoom.h"
#include "MessageQueue.h"

namespace message {

	class CategoryRoom : public BaseRoom {
		std::shared_ptr<MessageQueue> message_queue_;

	public:
		CategoryRoom() = default;
		CategoryRoom(const std::string& room_name);
		virtual ~CategoryRoom();

		// Call by sender
		void push_message(std::string&& message);
		MessageChannelPtr get_channel_ptr();
	};
}