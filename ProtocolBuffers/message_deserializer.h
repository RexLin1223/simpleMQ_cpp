#pragma once
#include "reflection.pb.h"
#include <string>
#include <memory>

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace proto
{
	class message_deserializer
	{
	public:				
		static std::shared_ptr<google::protobuf::Message> deserialize(const char* buffer, size_t length);		

	private:
		static std::shared_ptr<google::protobuf::Message> create_message(const std::string& type_name);
	};	
}