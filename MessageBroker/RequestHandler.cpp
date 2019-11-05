#include "RequestHandler.h"
#include "message.pb.h"

namespace message {

	RequestHandler::RequestHandler(boost::asio::ip::tcp::socket socket)
		: socket_(std::move(socket))
	{
		
	}

	RequestHandler::~RequestHandler()
	{

	}

	void RequestHandler::run()
	{
		auto self = shared_from_this();
		boost::asio::async_read(socket_, read_buffer_,
			[self, this](boost::system::error_code ec, std::size_t byte_transferred) {
			if (!ec) {
				read_buffer_.commit(byte_transferred);

				const char *data_ptr = boost::asio::buffer_cast<const char*>(read_buffer_.data());

				// TODO deserialize
				auto data = std::string(data_ptr, byte_transferred);
				if (on_visitor_) on_visitor_(data);

				read_buffer_.consume(byte_transferred);
			}
		});
	}

	void RequestHandler::set_hanlder(OnVisitor on_visitor)
	{
		on_visitor_ = on_visitor;
	}

}