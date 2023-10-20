#pragma once

#include <string>

namespace Source2Py {

	class PyAPI {
	public:

		// Print message to console
		static void ConPrint(std::string message);

		// Print message in client console
		static void ClientConPrint(int playerSlot, std::string message);

		// Issue server command
		static void ServerCommand(const std::string& command);

		// Issue client command (mimics client entering command in console)
		static void ClientCommand(int playerSlot, const std::string& command);

		// Set timescale
		static void SetTimescale(float timeScale);
	};
}