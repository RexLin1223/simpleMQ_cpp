#pragma once
#include <string>
#include "BaseRoom.h"

namespace message {
	class BaseRoom;

	class TopicRoom : public BaseRoom {
		std::shared_ptr<BaseRoom> category_room_;
	public:
		TopicRoom() = default;
		TopicRoom(const std::string& room_name, 
			std::shared_ptr<BaseRoom> category_room);
		virtual ~TopicRoom();
	};
}