#include "TopicRoom.h"
#include "BaseRoom.h"

namespace message {

	TopicRoom::TopicRoom(
		const std::string& room_name
	    , std::shared_ptr<BaseRoom> category_room)
		: BaseRoom(room_name)
		, category_room_(category_room)
	{
	}

	TopicRoom::~TopicRoom()
	{

	}

}