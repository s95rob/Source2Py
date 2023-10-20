#pragma once

#include "PyPlugin.h"

#include <ISmmPlugin.h>
#include <igameevents.h>
#include <iplayerinfo.h>
#include <sh_vector.h>

#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

namespace Source2Py {


	class Source2PyPlugin : public ISmmPlugin, public IMetamodListener {
	public:
		Source2PyPlugin();

		bool LoadPythonPlugins();

		// Get this plugin's directory path
		static fs::path GetPluginBaseDirectory() { return s_Source2PyDirectory; }

		// IS2mmPlugin overrides
		virtual bool Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late) override;
		virtual bool Unload(char* error, size_t maxlen) override;
		virtual bool Pause(char* error, size_t maxlen) override;
		virtual bool Unpause(char* error, size_t maxlen) override;

		// Hooks
		void Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick);
		void Hook_ClientActive(CPlayerSlot slot, bool bLoadGame, const char* pszName, uint64 xuid);
		void Hook_ClientDisconnect(CPlayerSlot slot, int reason, const char* pszName, uint64 xuid, const char* pszNetworkID);
		void Hook_ClientPutInServer(CPlayerSlot slot, char const* pszName, int type, uint64 xuid);
		void Hook_ClientSettingsChanged(CPlayerSlot slot);
		void Hook_OnClientConnected(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, const char* pszAddress, bool bFakePlayer);
		bool Hook_ClientConnect(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, bool unk1, CBufferString* pRejectReason);
		void Hook_ClientCommand(CPlayerSlot nSlot, const CCommand& _cmd);

		// Plugin meta information
        virtual const char* GetAuthor() override { return "s95rob"; }
        virtual const char* GetName() override { return "Source2Py"; }
        virtual const char* GetDescription() override { return "Python for Source 2"; }
        virtual const char* GetURL() override { return "N/A"; }
        virtual const char* GetLicense() override { return "GPL-3.0"; }
        virtual const char* GetVersion() override { return "1.0a"; }
        virtual const char* GetDate() override { return __DATE__; }
        virtual const char* GetLogTag() override { return "N/A"; }

	private:
		std::vector<PyPlugin> m_Plugins;
		static fs::path s_Source2PyDirectory;
	};

    extern Source2PyPlugin g_Source2PyPlugin;
}