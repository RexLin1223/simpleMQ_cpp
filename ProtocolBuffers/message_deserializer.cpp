#include "message_deserializer.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

namespace proto
{

	std::shared_ptr<google::protobuf::Message> message_deserializer::create_message(const std::string& type_name)
	{
		std::shared_ptr<google::protobuf::Message> message = nullptr;
		const google::protobuf::Descriptor* descriptor =
			google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
		if (descriptor)
		{
			const google::protobuf::Message* prototype =
				google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
			if (prototype)
			{
				message = std::shared_ptr<google::protobuf::Message>(prototype->New());
			}
		}
		return message;
	}

	std::shared_ptr<google::protobuf::Message> message_deserializer::deserialize(const char* buffer, size_t length)
	{
		proto::proto_message proto_message;
		proto_message.ParseFromArray(buffer, length);

		std::shared_ptr<google::protobuf::Message> message = message_deserializer::create_message(proto_message.type());
		if (message)
		{
			message->ParseFromString(proto_message.payload());
		}		

		return message;
	}	
}