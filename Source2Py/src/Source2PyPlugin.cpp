#include "Source2Py.h"
#include "Log.h"
#include "PyRuntime.h"

#include <iserver.h>

namespace Source2Py {

    PLUGIN_GLOBALVARS();

    SH_DECL_HOOK3_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool, bool, bool);
    SH_DECL_HOOK4_void(IServerGameClients, ClientActive, SH_NOATTRIB, 0, CPlayerSlot, bool, const char*, uint64);
    SH_DECL_HOOK5_void(IServerGameClients, ClientDisconnect, SH_NOATTRIB, 0, CPlayerSlot, int, const char*, uint64, const char*);
    SH_DECL_HOOK4_void(IServerGameClients, ClientPutInServer, SH_NOATTRIB, 0, CPlayerSlot, char const*, int, uint64);
    SH_DECL_HOOK1_void(IServerGameClients, ClientSettingsChanged, SH_NOATTRIB, 0, CPlayerSlot);
    SH_DECL_HOOK6_void(IServerGameClients, OnClientConnected, SH_NOATTRIB, 0, CPlayerSlot, const char*, uint64, const char*, const char*, bool);
    SH_DECL_HOOK6(IServerGameClients, ClientConnect, SH_NOATTRIB, 0, bool, CPlayerSlot, const char*, uint64, const char*, bool, CBufferString*);
    SH_DECL_HOOK2(IGameEventManager2, FireEvent, SH_NOATTRIB, 0, bool, IGameEvent*, bool);

    SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, CPlayerSlot, const CCommand&);


    Source2PyPlugin g_Source2PyPlugin;
    IServerGameDLL* server = NULL;
    IServerGameClients* gameclients = NULL;
    IVEngineServer* engine = NULL;
    IGameEventManager2* gameevents = NULL;
    ICvar* icvar = NULL;
    PLUGIN_EXPOSE(Source2PyPlugin, g_Source2PyPlugin);

    bool Source2PyPlugin::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late) {
        bool success = true;

        Log::Write("Loading plugin...");

        PLUGIN_SAVEVARS();

        GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
        GET_V_IFACE_CURRENT(GetEngineFactory, icvar, ICvar, CVAR_INTERFACE_VERSION);
        GET_V_IFACE_ANY(GetServerFactory, server, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
        GET_V_IFACE_ANY(GetServerFactory, gameclients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
        GET_V_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);

        SH_ADD_HOOK_MEMFUNC(IServerGameDLL, GameFrame, server, this, &Source2PyPlugin::Hook_GameFrame, true);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientActive, gameclients, this, &Source2PyPlugin::Hook_ClientActive, true);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, gameclients, this, &Source2PyPlugin::Hook_ClientDisconnect, true);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, gameclients, this, &Source2PyPlugin::Hook_ClientPutInServer, true);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientSettingsChanged, gameclients, this, &Source2PyPlugin::Hook_ClientSettingsChanged, false);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, OnClientConnected, gameclients, this, &Source2PyPlugin::Hook_OnClientConnected, false);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientConnect, gameclients, this, &Source2PyPlugin::Hook_ClientConnect, false);
        SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientCommand, gameclients, this, &Source2PyPlugin::Hook_ClientCommand, false);

        // Temporarily set current working directory to this plugin's directory
        fs::path exePath = fs::current_path(); // save for later
        fs::current_path(GetPluginBaseDirectory());

        if (!PyRuntime::Init())
            success = false;

        if (!LoadPythonPlugins()) {
            PyRuntime::Close();
            success = false;
        }

        // ...and set the cwd back where the game expects it
        fs::current_path(exePath);

        return success;
    }

    bool Source2PyPlugin::Unload(char* error, size_t maxlen) {
        SH_REMOVE_HOOK_MEMFUNC(IServerGameDLL, GameFrame, server, this, &Source2PyPlugin::Hook_GameFrame, true);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientActive, gameclients, this, &Source2PyPlugin::Hook_ClientActive, true);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, gameclients, this, &Source2PyPlugin::Hook_ClientDisconnect, true);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, gameclients, this, &Source2PyPlugin::Hook_ClientPutInServer, true);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientSettingsChanged, gameclients, this, &Source2PyPlugin::Hook_ClientSettingsChanged, false);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, OnClientConnected, gameclients, this, &Source2PyPlugin::Hook_OnClientConnected, false);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientConnect, gameclients, this, &Source2PyPlugin::Hook_ClientConnect, false);
        SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientCommand, gameclients, this, &Source2PyPlugin::Hook_ClientCommand, false);

        for (auto& plugin : m_Plugins)
            plugin.Unload();

        PyRuntime::Close();

        Log::Write("Plugin unloaded successfully");

        return true;
    }

    bool Source2PyPlugin::Pause(char* error, size_t maxlen) {
        // unused
        return true;
    }

    bool Source2PyPlugin::Unpause(char* error, size_t maxlen) {
        // unused
        return true;
    }

    void Source2PyPlugin::Hook_ClientActive(CPlayerSlot slot, bool bLoadGame, const char* pszName, uint64 xuid) {
        for (auto& plugin : m_Plugins)
            plugin.ClientActive(slot.Get(), bLoadGame, pszName, xuid);
    }

    void Source2PyPlugin::Hook_ClientCommand(CPlayerSlot slot, const CCommand& args) {
        // todo
    }

    void Source2PyPlugin::Hook_ClientSettingsChanged(CPlayerSlot slot) {
        for (auto& plugin : m_Plugins)
            plugin.ClientSettingsChanged(slot.Get());
    }

    void Source2PyPlugin::Hook_OnClientConnected(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, const char* pszAddress, bool bFakePlayer) {
        for (auto& plugin : m_Plugins)
            plugin.OnClientConnected(slot.Get(), pszName, xuid, pszNetworkID, pszAddress, bFakePlayer);
    }

    bool Source2PyPlugin::Hook_ClientConnect(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, bool unk1, CBufferString* pRejectReason) {
        for (auto& plugin : m_Plugins)
            plugin.ClientConnect(slot.Get(), pszName, xuid, pszNetworkID);

        RETURN_META_VALUE(MRES_IGNORED, true);
    }

    void Source2PyPlugin::Hook_ClientPutInServer(CPlayerSlot slot, char const* pszName, int type, uint64 xuid) {
        for (auto& plugin : m_Plugins)
            plugin.ClientPutInServer(slot.Get(), pszName, type, xuid);
    }

    void Source2PyPlugin::Hook_ClientDisconnect(CPlayerSlot slot, int reason, const char* pszName, uint64 xuid, const char* pszNetworkID) {
        for (auto& plugin : m_Plugins)
            plugin.ClientDisconnect(slot.Get(), reason, pszName, xuid, pszNetworkID);
    }

    void Source2PyPlugin::Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick) {
        for (auto& plugin : m_Plugins)
            plugin.GameFrame(simulating, bFirstTick, bLastTick);
    }
}