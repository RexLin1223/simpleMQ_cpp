#pragma once
#include <string>
#include "BaseRoom.h"
#include <Common/LockedContainer.h>

namespace message {
	class TopicRoom;
	class CategoryRoom : public BaseRoom {
		queue::LockedMap<std::string, std::weak_ptr<TopicRoom>> topic_rooms_;

	public:
		CategoryRoom() = default;
		CategoryRoom(const std::string& room_name);
		virtual ~CategoryRoom();

		std::shared_ptr<BaseRoom> get_topic_room(const std::string& topic);

	private:
		std::shared_ptr<BaseRoom> create_topic_room(const std::string& topic);
	};
}