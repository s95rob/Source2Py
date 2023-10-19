#pragma once

#include <ISmmPlugin.h>

namespace Source2Py {

	class Source2PyPlugin : public ISmmPlugin, public IMetamodListener {
	public:
		Source2PyPlugin() = default;

		virtual bool Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlength, bool late) override;

    private:

    // Plugin meta information
    public:
        virtual const char* GetAuthor() override { return "s95rob"; }
        virtual const char* GetName() override { return "Source2Py"; }
        virtual const char* GetDescription() override { return "Python for Source 2"; }
        virtual const char* GetURL() override { return "N/A"; }
        virtual const char* GetLicense() override { return "GPL-3.0"; }
        virtual const char* GetVersion() override { return "1.0a"; }
        virtual const char* GetDate() override { return __DATE__; }
        virtual const char* GetLogTag() override { return "N/A"; }
	};
}