#pragma once
#include "BaseVisitor.h"

namespace message {
	class Receiver : public BaseVisitor{
	public:
		Receiver(VisitorInfo&& properties);
		virtual ~Receiver();

		void run() override;
		void set_channel(MessageChannelPtr channel) override;

	private:
		void on_message(std::shared_ptr<std::string> message);
	};
}