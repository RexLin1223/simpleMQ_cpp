#include <string>
#include <iostream>

namespace logger {
	template<typename T>
	static void error(const std::string& category, T&& content) {
		std::cout << "[Error] " << category << ": " << content << std::endl;
	}

	template<typename T>
	static void info(const std::string& category, T&& content){
		std::cout << "[Info] " << category << ": " << content << std::endl;
	}

	template<typename T>
	static void debug(const std::string& category, T&& content){
		std::cout << "[Debug] " << category << ": " << content << std::endl;
	}
}