#pragma once
#include "reflection.pb.h"
#include <string>

namespace proto
{
	class message_serializer
	{
	public:
		template<typename T>
		static std::string serialize(const T& message);

		template<typename T>
		static std::string serialize(const T& message, const std::string& full_name);

	private:
		static std::string wrap(const std::string& strbuf, const std::string& full_name);
	};

	template<typename T>
	std::string message_serializer::serialize(const T& message)
	{
		return message_serializer::serialize(message, message.descriptor()->full_name());		
	}

	template<typename T>
	std::string message_serializer::serialize(const T& message, const std::string& full_name)
	{
		std::string strbuf;
		message.SerializeToString(&strbuf);

		return wrap(strbuf, full_name);
	}
}