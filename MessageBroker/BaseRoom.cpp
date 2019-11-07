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

	
	MessageChannelPtr BaseRoom::get_channel()
	{
		return channel_;
	}

}