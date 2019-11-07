#pragma once
#include <Common/LockedContainer.h>

namespace message {
	// Forward declaration
	class Sender;
	class Receiver;
	class CategoryRoom;

	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	using MessageChannelPtr = std::shared_ptr<MessageChannel>;

	class RoomManager {
		queue::LockedMap<std::string, std::shared_ptr<CategoryRoom>> map_;
	public:
		RoomManager() = default;
		virtual ~RoomManager();

		MessageChannelPtr get_room_channel(
			const std::string& room_name,
			const std::string& topic);

		size_t room_count();

	private:
		bool create_room(const std::string& room_name);
	};
}