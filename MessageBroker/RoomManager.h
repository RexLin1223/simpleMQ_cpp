#pragma once
#include <Common/LockedContainer.h>

namespace message {
	// Forward declaration
	class Sender;
	class Receiver;
	class BaseRoom;
	class CategoryRoom;

	class RoomManager {
		boost::mutex mutex_;
		queue::LockedMap<std::string, std::weak_ptr<CategoryRoom>> map_;
	public:
		RoomManager() = default;
		virtual ~RoomManager();

		std::shared_ptr<BaseRoom> get_room(
			const std::string& room_name,
			const std::string& topic);

		size_t room_count();

	private:
		
		std::shared_ptr<BaseRoom> create_room(const std::string& room_name);
	};
}