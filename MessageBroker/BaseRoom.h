#pragma once
#include <string>
#include <memory>

namespace message {
	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	using MessageChannelPtr = std::shared_ptr<MessageChannel>;

	class BaseRoom : public std::enable_shared_from_this<BaseRoom> {
	protected:
		std::string room_name_;
		MessageChannelPtr channel_;
		
		BaseRoom() = default;
		BaseRoom(const std::string& room_name);
		virtual ~BaseRoom();
		
	public:
		MessageChannelPtr get_channel();
	};
	
}