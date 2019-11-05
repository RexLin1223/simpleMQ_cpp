#pragma once
#include "BaseVisitor.h"

namespace message {
	class Receiver : public BaseVisitor{
	public:
		Receiver(VisitorProperties&& properties);
		virtual ~Receiver();

	private:
		void on_message(std::shared_ptr<std::string> message);
	};
}