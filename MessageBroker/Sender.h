#pragma once
#include "BaseVisitor.h"
#include <Common/MessageChannel.h>

namespace proto {
	class message_dispatcher;
}

namespace message {
	template<typename> class Channel;
	using MessageChannel = Channel<std::string>;
	class PublisherMessage;

	class Sender : public BaseVisitor {
		boost::asio::streambuf read_buffer_;

		std::shared_ptr<proto::message_dispatcher> message_dispatcher_;

		std::shared_ptr<BaseRoom> room_;
		std::shared_ptr<MessageChannel> channel_;
	public:
		Sender(VisitorInfo&& properties, std::shared_ptr<Worker> worker);
		virtual ~Sender();

		void run() override;
		void set_room(std::shared_ptr<BaseRoom> room) override;
	private:
		void read_header();
		void read_body(uint32_t body_size);
		void on_message(const std::shared_ptr<PublisherMessage> pubMessage);
	};
}