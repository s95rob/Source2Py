#include "Source2Py.h"

#include <iostream>

namespace Source2Py {

	Source2PyPlugin g_Source2PyPlugin;
	PLUGIN_EXPOSE(Source2PyPlugin, g_Source2PyPlugin);

    bool Source2PyPlugin::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlength, bool late) {
        std::cout << "Source2Py loaded!\n";

        return true;
    }
}