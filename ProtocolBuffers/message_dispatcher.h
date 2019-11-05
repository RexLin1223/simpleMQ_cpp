#pragma once
#include "message_handler.h"
#include <memory>
#include <map>

namespace google
{
	namespace protobuf
	{
		class Message;
		class Descriptor;
	}
}

namespace proto
{		
	class message_dispatcher
	{
	public:
		message_dispatcher();
		virtual ~message_dispatcher();

		template<typename T>
		void register_handler(const typename message_handlerT<T>::handle_message_function& functor);			
		void dispatch(const std::shared_ptr<google::protobuf::Message> message) const;

	private:
		virtual void OnUnknowunMessage(const std::shared_ptr<google::protobuf::Message> message) const;
		
	private:
		typedef std::map<const google::protobuf::Descriptor*, std::shared_ptr<message_handler>> handler_map;
		handler_map handlers_;
	};

	template<typename T>
	void message_dispatcher::register_handler(const typename message_handlerT<T>::handle_message_function& functor)
	{
		std::shared_ptr<message_handlerT<T>> handler = std::make_shared<message_handlerT<T>>(functor);
		handlers_[T::descriptor()] = handler;
	}
}