#pragma once
#include "MessageChannel.h"
#include <Common/LockedContainer.h>
#include <Common/Worker.h>

namespace message {
	typedef queue::LockedLinkList<std::shared_ptr<std::string>> MessagePtrList;
	
	class MessageQueue : public Worker {
		MessagePtrList queue_;
		MessageChannelPtr channel_;
	public:
		MessageQueue(size_t worker_count);
		virtual ~MessageQueue() {}

		void set_channel(MessageChannelPtr channel);

		void push(std::string&& message);
		size_t size();
	private:
		void dispatch();
	};
}
