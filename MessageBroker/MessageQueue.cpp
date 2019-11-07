#pragma once
#include "MessageQueue.h"

namespace message {
	MessageQueue::MessageQueue(size_t worker_count)
		: Worker(worker_count)
		, channel_(nullptr) {
		Worker::run();
	}

	void MessageQueue::set_channel(MessageChannelPtr channel)
	{
		channel_ = channel;
	}

	void MessageQueue::push(std::string&& message)
	{
		try {
			queue_.push(std::make_shared<std::string>(std::move(message)));
		}
		catch (...) {
			return;
		}

		io_context_.post([this]() {
			dispatch();
		});
	}

	size_t MessageQueue::size()
	{
		return queue_.size();
	}

	void MessageQueue::dispatch()
	{
		if (!queue_.empty() && channel_) {
			channel_->broadcast(queue_.fetch());
		}
	}

}