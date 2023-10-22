#include "PyPlugin.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace Source2Py {

	bool PyPlugin::LoadFromFile(std::string filepath) {
		std::string modulename = fs::path(filepath).stem().string();

		// Format filepath into module path for Python
		filepath.erase(filepath.find_last_of('.'), filepath.size());
		for (char& c : filepath) {
			if (c == '/' || c == '\\')
				c = '.';
		}

		// Attempt to load Python plugin
		try {
			m_PluginObject = py::module_::import(filepath.c_str()).attr(modulename.c_str());
		}
		catch (py::error_already_set& e) {
			Log::Error("Failed to load Python plugin: " + filepath + "\n" + std::string(e.what()));
			m_Valid = false;
		}

		return m_Valid;
	}

	void PyPlugin::Load() {
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnPluginLoad");
	}

	void PyPlugin::Unload() {
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnPluginUnload");
	}

	void PyPlugin::GameFrame(bool simulating, bool firstTick, bool lastTick) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnGameFrame", simulating, firstTick, lastTick);
	}

	void PyPlugin::ClientActive(int playerSlot, bool loadGame, const char* name, uint64_t xuid) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientActive", playerSlot, loadGame, name, xuid);
	}

	void PyPlugin::ClientDisconnect(int playerSlot, int reason, const char* name, uint64_t xuid, const char* networkID) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientDisconnect", playerSlot, reason, name, xuid, networkID);
	}

	void PyPlugin::ClientPutInServer(int playerSlot, char const* name, int type, uint64_t xuid) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientPutInServer", playerSlot, name, type, xuid);
	}

	void PyPlugin::ClientSettingsChanged(int playerSlot) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientSettingsChanged", playerSlot);
	}

	void PyPlugin::OnClientConnected(int playerSlot, const char* name, uint64_t xuid, const char* networkID, const char* address, bool fakePlayer) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientConnected", playerSlot, name, xuid, networkID, address, fakePlayer);
	}

	void PyPlugin::ClientConnect(int playerSlot, const char* name, uint64_t xuid, const char* networkID) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientConnect", playerSlot, name, xuid, networkID);
	}

	void PyPlugin::FireGameEvent(IGameEvent* event) {
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnGameEvent", event);
	}

}