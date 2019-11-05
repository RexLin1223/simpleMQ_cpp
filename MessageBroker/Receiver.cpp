#include "Receiver.h"

namespace message {

	Receiver::Receiver(VisitorProperties&& properties)
		: BaseVisitor(std::move(properties))
	{

	}

	Receiver::~Receiver()
	{

	}

	void Receiver::on_message(std::shared_ptr<std::string> serializedMessage)
	{
		// Send to receiver
		boost::asio::async_write(properties_.socket_,
			boost::asio::buffer(serializedMessage->data(), 
				serializedMessage->size()),
			[serializedMessage, this]
		(boost::system::error_code ec,
			std::size_t byte_transferred) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				if (on_close_) {
					on_close_();
				}
			}
		});
	}
}