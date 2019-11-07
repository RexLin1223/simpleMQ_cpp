#include "RoomManager.h"
#include "MessageChannel.h"
#include "MessageQueue.h"

#include "CategoryRoom.h"

#include <Common/Utility.h>

namespace message {
	
	RoomManager::~RoomManager()
	{

	}

	MessageChannelPtr RoomManager::get_room_channel(const std::string& category, const std::string& topic)
	{
		if (!map_.try_find(category)) {
			create_room(category);
		}
		
		auto room_ptr = map_.peek(category);
		if (!topic.empty()) {
			return room_ptr->get_topic_channel(topic);
		}
		else {
			return  room_ptr->get_channel();
		}
	}

	size_t RoomManager::room_count()
	{
		return map_.size();
	}

	bool RoomManager::create_room(const std::string& room_name)
	{
		try {
			map_.insert(std::string(room_name), std::make_shared<CategoryRoom>(room_name));
			return true;
		}
		catch (...) {
		}
		return false;
	}

}