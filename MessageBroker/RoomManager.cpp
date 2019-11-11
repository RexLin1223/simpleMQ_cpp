#include "RoomManager.h"
#include <Common/MessageChannel.h>

#include "CategoryRoom.h"

#include <Common/Utility.h>

namespace message {
	
	RoomManager::~RoomManager()
	{

	}

	std::shared_ptr<BaseRoom> RoomManager::get_room(const std::string& category, const std::string& topic)
	{
		std::shared_ptr<BaseRoom> room_ptr;
		if (!map_.try_find(category)) {
			room_ptr = create_room(category);
		}
		else {
			auto room_weak_ptr = map_.peek(category);
			room_ptr = room_weak_ptr.lock();

			if (!room_ptr) {
				room_ptr = create_room(category);
			}
		}

		if (!topic.empty()) {
			return std::dynamic_pointer_cast<CategoryRoom>(room_ptr)->get_topic_room(topic);
		}
		else {
			return room_ptr;
		}
	}

	size_t RoomManager::room_count()
	{
		return map_.size();
	}

	std::shared_ptr<BaseRoom> RoomManager::create_room(const std::string& room_name)
	{
		try {
			auto room_ptr = std::make_shared<CategoryRoom>(room_name);
			map_.insert(std::string(room_name), room_ptr);
			return room_ptr;
		}
		catch (...) {
		}
		return false;
	}

}