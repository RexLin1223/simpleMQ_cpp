#pragma once
#include "LockedContainer.h"

namespace message {
	// Forward declaration
	class Sender;
	class Receiver;
	class CategoryRoom;

	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	using MessageChannelPtr = std::shared_ptr<MessageChannel>;

	class RoomManager {
		queue::LockedMap<std::string, CategoryRoom> map_;
	public:
		MessageChannelPtr get_room_channel(const std::string& room_name);
		size_t room_size();

	private:
		bool create_room(const std::string& room_name);
	};
}