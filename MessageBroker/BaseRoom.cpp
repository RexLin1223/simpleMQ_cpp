#include "BaseRoom.h"

namespace message {
	BaseRoom::BaseRoom(const std::string& room_name)
		: room_name_(room_name)
		, channel_(std::make_shared<MessageChannel>())
	{
	}

	BaseRoom::~BaseRoom()
	{
		channel_.reset();
	}
	
	void BaseRoom::join(ChannelListener&& listener)
	{
		if (channel_) {
			channel_->subscribe(std::move(listener));
		}
	}

	void BaseRoom::left(const std::string& listener_id)
	{
		if (channel_) {
			channel_->desubscribe(listener_id);
		}
	}
}