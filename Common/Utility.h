#pragma once
#include <functional>
#include <string>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

namespace message {
	// Type definition
	using OnError = std::function<void(const std::string&)>;
	using OnClose = std::function<void()>;
	using OnData = std::function<void(std::shared_ptr<std::string>)>;

	const char start_code[4] = { 0x00, 0x00, 0x01, 0xb2 };

	// Static utility function
	static std::string get_uuid() {
		boost::uuids::uuid uid = boost::uuids::random_generator()();
		return boost::lexical_cast<std::string>(uid);
	}

	static bool check_start_code(const char* data_ptr) {
		return (
			data_ptr[0] == 0x00 && 
			data_ptr[1] == 0x00 &&
			data_ptr[2] == 0x01 && 
			(unsigned char)data_ptr[3] == 0xb2);
	}
}