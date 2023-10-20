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
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "Load");
	}

	void PyPlugin::Unload() {
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "Unload");
	}

	void PyPlugin::GameFrame(bool simulating, bool firstTick, bool lastTick) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "GameFrame", simulating, firstTick, lastTick);
	}

	void PyPlugin::ClientActive(int playerSlot, bool loadGame, const char* name, uint64_t xuid) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "ClientActive", playerSlot, loadGame, name, xuid);
	}

	void PyPlugin::ClientDisconnect(int playerSlot, int reason, const char* name, uint64_t xuid, const char* networkID) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "ClientDisconnect", playerSlot, reason, name, xuid, networkID);
	}

	void PyPlugin::ClientPutInServer(int playerSlot, char const* name, int type, uint64_t xuid) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "ClientPutInServer", playerSlot, name, type, xuid);
	}

	void PyPlugin::ClientSettingsChanged(int playerSlot) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "ClientSettingsChanged", playerSlot);
	}

	void PyPlugin::OnClientConnected(int playerSlot, const char* name, uint64_t xuid, const char* networkID, const char* address, bool fakePlayer) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "OnClientConnected", playerSlot, name, xuid, networkID, address, fakePlayer);
	}

	void PyPlugin::ClientConnect(int playerSlot, const char* name, uint64_t xuid, const char* networkID) { 
		PyRuntime::ExecuteObjectMethod(m_PluginObject, "ClientConnect", playerSlot, name, xuid, networkID);
	}

}