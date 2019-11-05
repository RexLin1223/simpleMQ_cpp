#pragma once
#include "Utility.h"
#include "Worker.h"
namespace message {

	struct VisitorProperties {
		boost::asio::ip::tcp::socket socket_;
		std::string category;
		std::string topic;
		std::string unique_id;
	};

	class BaseVisitor : public Worker, public std::enable_shared_from_this<BaseVisitor> {
		VisitorProperties properties_;
		BaseVisitor(VisitorProperties&& properties);
		virtual ~BaseVisitor();

		OnError on_error_;
		OnClose on_close_;

	public:
		void set_on_error(OnError&& on_error);
		void set_on_close(OnClose&& on_close);

		void start();
		void stop();

	private:
		void timer_worker();
		void send_alive();
	};
	
}