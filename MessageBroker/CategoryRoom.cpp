#include "CategoryRoom.h"
#include "TopicRoom.h"

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

	MessageChannelPtr CategoryRoom::get_topic_channel(const std::string& topic)
	{
		if (!topic_rooms_.try_find(topic)) return nullptr;
		
		auto room_ptr = topic_rooms_.peek(topic);
		if (!room_ptr) return nullptr;
		
		return room_ptr->get_channel();
	}

	void CategoryRoom::push_message(std::string&& message)
	{
		if (message_queue_) {
			message_queue_->push(std::move(message));
		}
	}
	
}