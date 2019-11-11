#pragma once
#include <string>
#include "BaseRoom.h"

namespace message {
	class BaseRoom;

	class TopicRoom : public BaseRoom {
	public:
		TopicRoom() = default;
		TopicRoom(const std::string& room_name);
		virtual ~TopicRoom();
	};
}