#include "PyAPI.h"

#include <ISmmPlugin.h>

namespace Source2Py {

	PLUGIN_GLOBALVARS();

	extern IVEngineServer* engine;

	void PyAPI::ConPrint(std::string message) {
		message.append("\n");
		META_CONPRINT(message.c_str());
	}

	void PyAPI::ClientConPrint(int playerSlot, std::string message) {
		message.append("\n");
		engine->ClientPrintf(playerSlot, message.c_str());
	}

	void PyAPI::ServerCommand(const std::string& command) {
		engine->ServerCommand(command.c_str());
	}

	void PyAPI::ClientCommand(int playerSlot, const std::string& command) {
		engine->ClientCommand(playerSlot, command.c_str());
	}

	void PyAPI::SetTimescale(float timeScale) {
		engine->SetTimescale(timeScale);
	}
}