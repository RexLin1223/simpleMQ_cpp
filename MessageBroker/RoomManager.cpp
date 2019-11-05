#include "RoomManager.h"
#include "MessageChannel.h"
#include "MessageQueue.h"

#include "CategoryRoom.h"

#include "Utility.h"

namespace message {
	
	MessageChannelPtr RoomManager::get_room_channel(const std::string& room_name)
	{
		if (!map_.try_find(room_name)) {
			// Create room if not exist
			create_room(room_name);
		}
		
		CategoryRoom* room_ptr = map_.peek(room_name);
		return  room_ptr->get_channel_ptr();
	}

	size_t RoomManager::room_size()
	{
		return map_.size();
	}

	bool RoomManager::create_room(const std::string& room_name)
	{
		try {
			CategoryRoom room = CategoryRoom(room_name);
			map_.insert(room_name, room);
			return true;
		}
		catch (...) {
		}
		return false;
	}

}