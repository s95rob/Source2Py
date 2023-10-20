#include "Source2Py.h"

#include <fstream>

namespace Source2Py {

	// Maybe this shouldn't be hardcoded...
	fs::path Source2PyPlugin::s_Source2PyDirectory = "../../csgo/addons/Source2Py/";

	Source2PyPlugin::Source2PyPlugin() {
		Log::Write("Source2PyPlugin created");
	}

	bool Source2PyPlugin::LoadPythonPlugins() {
		fs::path pypluginsFilepath = "pyplugins.ini";

		if (!fs::exists(pypluginsFilepath)) {
			Log::Error("Failed to load pyplugins.ini!");
			return false;
		}

		// Read from pyplugins.ini
		std::ifstream pypluginsFile(pypluginsFilepath);

		if (pypluginsFile.fail()) {
			Log::Error("Failed to open pyplugins.ini!");
			return false;
		}

		std::string line;
		while (std::getline(pypluginsFile, line)) {
			// ignore comments
			if (line[0] == '#' || line[0] == ';')
				continue;

			PyPlugin plugin(line);
			if (plugin) {
				m_Plugins.push_back(plugin);
				m_Plugins.back().Load();
			}
		}

		Log::Write("Loaded " + std::to_string(m_Plugins.size()) + " Python plugins");

		return true;
	}
}