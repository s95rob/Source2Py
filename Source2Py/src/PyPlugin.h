#pragma once

#include "PyRuntime.h"

#include <igameevents.h>

namespace Source2Py {

	class PyPlugin {
	public:
		PyPlugin() = default;
		PyPlugin(std::string filepath) { this->LoadFromFile(filepath); }

		bool LoadFromFile(std::string filepath);

		// Python plugin methods
		void Load();
		void Unload();

		// Python plugin hooks
		void GameFrame(bool simulating, bool firstTick, bool lastTick);
		void ClientActive(int playerSlot, bool loadGame, const char* name, uint64_t xuid);
		void ClientDisconnect(int playerSlot, int reason, const char* name, uint64_t xuid, const char* networkID);
		void ClientPutInServer(int playerSlot, char const* name, int type, uint64_t xuid);
		void ClientSettingsChanged(int playerSlot);
		void OnClientConnected(int playerSlot, const char* name, uint64_t xuid, const char* networkID, const char* address, bool fakePlayer);
		void ClientConnect(int playerSlot, const char* name, uint64_t xuid, const char* networkID);
		//void ClientCommand(int playerSlot, const CCommand& _cmd); (todo: port CCommand)
		void FireGameEvent(IGameEvent* event);

		bool IsValid() const { return m_Valid; }

		operator bool() { return m_Valid; }

	private:
		py::object m_PluginObject;
		bool m_Valid = true;
	};
}