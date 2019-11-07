#pragma once
#include "MessageBrokerDef.h"
#include <Common/Worker.h>
#include <Common/Utility.h>

namespace message {
	// Forward declaration
	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	using MessageChannelPtr = std::shared_ptr<MessageChannel>;
	class BaseVisitor : public Worker, public std::enable_shared_from_this<BaseVisitor> {
	protected:
		VisitorInfo properties_;

		BaseVisitor(VisitorInfo&& properties);
		virtual ~BaseVisitor();

		OnError on_error_;
		OnClose on_close_;

		void timer_worker();
		void send_alive();
	
		void start();
		void stop();
	public:
		void set_on_error(OnError&& on_error);
		void set_on_close(OnClose&& on_close);

		virtual void run() = 0;
		virtual void set_channel(MessageChannelPtr channel) = 0;

		VisitorInfo::Type get_type();
		std::string get_category();
		std::string get_topic();
		std::string get_uid();
	};
	
}