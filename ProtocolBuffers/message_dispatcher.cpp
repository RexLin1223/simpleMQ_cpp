#include "message_dispatcher.h"
#include <iostream>
#include <google/protobuf/message.h>

namespace proto
{

	message_dispatcher::message_dispatcher()
	{

	}

	message_dispatcher::~message_dispatcher()
	{

	}
		
	void message_dispatcher::dispatch(const std::shared_ptr<google::protobuf::Message> message) const
	{
		if (!message)
		{
			return;
		}

		handler_map::const_iterator it = handlers_.find(message->GetDescriptor());
		if (it != handlers_.end())
		{
			it->second->OnMessage(message);
		}
		else 
		{
			OnUnknowunMessage(message);
		}
	}

	void message_dispatcher::OnUnknowunMessage(const std::shared_ptr<google::protobuf::Message> message) const
	{
		std::cout << "Unknown message :" << message->GetTypeName() << std::endl;
	}

}