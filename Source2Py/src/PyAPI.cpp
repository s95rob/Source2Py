#include "PyAPI.h"

#include <ISmmPlugin.h>

namespace Source2Py {

	PLUGIN_GLOBALVARS();

	void PyAPI::ConPrint(std::string& message) {
		message.append("\n");
		META_CONPRINT(message.c_str());
	}
}