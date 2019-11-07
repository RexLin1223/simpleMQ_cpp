#pragma once
#include <string>
#include "BaseRoom.h"
#include "MessageQueue.h"

namespace message {
	class TopicRoom;
	class CategoryRoom : public BaseRoom {
		std::shared_ptr<MessageQueue> message_queue_;
		queue::LockedMap<std::string, std::shared_ptr<TopicRoom>> topic_rooms_;

	public:
		CategoryRoom() = default;
		CategoryRoom(const std::string& room_name);
		virtual ~CategoryRoom();

		MessageChannelPtr get_topic_channel(const std::string& topic);

		// Call by sender
		void push_message(std::string&& message);
	};
}