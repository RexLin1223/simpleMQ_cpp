#include "TopicRoom.h"
#include "BaseRoom.h"

namespace message {

	TopicRoom::TopicRoom(std::string&& room_name)
		: BaseRoom(std::move(room_name))
	{

	}

	TopicRoom::~TopicRoom()
	{

	}

}