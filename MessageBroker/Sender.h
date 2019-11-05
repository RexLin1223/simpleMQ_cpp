#pragma once
#include "BaseVisitor.h"
#include "MessageChannel.h"

namespace message {
	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	using MessageChannelPtr = std::shared_ptr<MessageChannel>;

	class Sender : public BaseVisitor {
		MessageChannelPtr room_channel_;
		boost::asio::streambuf read_buffer_;
	public:
		Sender(VisitorProperties&& properties);
		virtual ~Sender();

		void run();
	private:
		void do_read();
	};
}