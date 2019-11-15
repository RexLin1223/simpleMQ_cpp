#pragma once
#include "MessageBrokerDef.h"
#include <Common/Utility.h>

namespace message {
	// Forward declaration
	class Worker;
	class BaseRoom;

	class BaseVisitor : public std::enable_shared_from_this<BaseVisitor> {
	protected:
		VisitorInfo properties_;
		std::shared_ptr<Worker> worker_;
		boost::asio::steady_timer timer_;

		BaseVisitor(
			VisitorInfo&& properties,
			std::shared_ptr<Worker> worker);
		virtual ~BaseVisitor();

		OnError on_error_;
		OnClose on_close_;

		void timer_worker();
		void send_alive();
	
		void start();
		void stop();

		template<typename Handler>
		void do_write(std::shared_ptr<std::vector<boost::asio::const_buffer>> buffer_array_ptr, Handler handler);

	public:
		void set_on_error(OnError&& on_error);
		void set_on_close(OnClose&& on_close);

		virtual void run() = 0;
		virtual void close() = 0;
		virtual void set_room(std::shared_ptr<BaseRoom> room) = 0;

		VisitorInfo::Type get_type();
		std::string get_category();
		std::string get_topic();
		std::string get_uid();
	};

	template<typename Handler>
	void message::BaseVisitor::do_write(std::shared_ptr<std::vector<boost::asio::const_buffer>> buffer_array_ptr, Handler handler)
	{
		boost::asio::async_write(
			properties_.socket_, 
			*buffer_array_ptr,
			handler);
	}

}