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

	// Static utility function
	static std::string get_uuid() {
		boost::uuids::uuid uid = boost::uuids::random_generator()();
		return boost::lexical_cast<std::string>(uid);
	}
}