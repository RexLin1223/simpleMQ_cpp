#pragma once
#include <string>
#include "BaseRoom.h"

namespace message {
	class BaseRoom;

	class TopicRoom : public BaseRoom {
	public:
		TopicRoom(std::string&& room_name);
		virtual ~TopicRoom();
	};
}