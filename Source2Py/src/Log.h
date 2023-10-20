#pragma once

#include <iostream>
#include <string_view>
#include <string>

namespace Source2Py {

	class Log {
	public:

		static void Write(std::string_view message) {
			std::cout << "[ Source2Py ] " << message << "\n";
		}

		static void Error(std::string_view message) {
			std::cerr << "[ Source2Py ] ERROR: " << message << "\n";
		}
	};
}