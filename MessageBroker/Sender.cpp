#include "Sender.h"
#include "MessageChannel.h"
namespace message {

	Sender::Sender(VisitorInfo&& properties)
		: BaseVisitor(std::move(properties))
	{
	}

	Sender::~Sender()
	{
		stop();
	}

	void Sender::run()
	{
		do_read();
		BaseVisitor::start();
	}

	void Sender::set_channel(MessageChannelPtr channel)
	{
		room_channel_ = channel;
	}

	void Sender::do_read()
	{
		boost::asio::async_read(properties_.socket_, read_buffer_,
			[this](boost::system::error_code ec, std::size_t transferred_bytes) {
			if (ec) {
				if (on_error_) {
					on_error_(ec.message().c_str());
				}
				if (on_close_) {
					on_close_();
				}
				return;
			}

			// Get data from buffer
			read_buffer_.commit(transferred_bytes);
			const char *data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());
			if (room_channel_) {
				// Serialize data to proto structure
				room_channel_->broadcast(std::string(data_ptr, transferred_bytes));
			}

			read_buffer_.consume(transferred_bytes);

			do_read();
		});
	}
}

