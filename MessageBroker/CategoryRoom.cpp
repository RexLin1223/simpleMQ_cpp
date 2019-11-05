#include "CategoryRoom.h"
#include "BaseRoom.h"

namespace message {

	CategoryRoom::CategoryRoom(const std::string& room_name)
		: BaseRoom(room_name)
	{
		message_queue_ = std::make_shared<MessageQueue>(1);
		message_queue_->set_channel(BaseRoom::channel_);
	}

	CategoryRoom::~CategoryRoom()
	{

	}

	void CategoryRoom::push_message(std::string&& message)
	{
		if (message_queue_) {
			message_queue_->push(std::move(message));
		}
	}

	MessageChannelPtr CategoryRoom::get_channel_ptr()
	{
		return channel_;
	}

}