#include "CategoryRoom.h"
#include "TopicRoom.h"

#include <Common/Logger.h>

namespace message {

	CategoryRoom::CategoryRoom(const std::string& room_name)
		: BaseRoom(room_name)
	{
	}

	CategoryRoom::~CategoryRoom()
	{
	}

	std::shared_ptr<BaseRoom> CategoryRoom::get_topic_room(const std::string& topic)
	{
		if (!topic_rooms_.try_find(topic)) {
			return create_topic_room(topic);
		}
		
		auto room_weak_ptr = topic_rooms_.peek(topic);
		auto room_ptr = room_weak_ptr.lock();
		return room_ptr;
	}
	
	std::shared_ptr<BaseRoom> CategoryRoom::create_topic_room(const std::string& topic)
	{
		logger::info("create_topic_room", topic);
		auto room_ptr = std::make_shared<TopicRoom>(topic, shared_from_this());
		topic_rooms_.insert(topic, room_ptr);

		return room_ptr;
	}

}