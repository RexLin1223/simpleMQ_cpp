#pragma once
#include <memory>
#include <functional>

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace proto
{
	class message_handler
	{
	public:
		virtual ~message_handler() {}
		virtual void OnMessage(const std::shared_ptr<google::protobuf::Message> message) const = 0;
	};

	template <typename T>
	class message_handlerT : public message_handler
	{
	public:
		typedef std::function<void(const std::shared_ptr<T> message)> handle_message_function;

		message_handlerT(const handle_message_function& handler)
			: handler_(handler)
		{

		}

		virtual void OnMessage(const std::shared_ptr<google::protobuf::Message> message) const
		{
			std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(message);
			handler_(t);
		}

	private:
		handle_message_function handler_;
	};
}