#include "PyRuntime.h"
#include "PyModule.h" // Include this once

namespace Source2Py {

	bool PyRuntime::s_InterpreterRunning = false;

	bool PyRuntime::Init() {
		if (s_InterpreterRunning) {
			Log::Error("PyRuntime is already running!");
			return false;
		}
		
		try {
			py::initialize_interpreter();
			s_InterpreterRunning = true;
		}
		catch (std::exception& e) {
			Log::Error(e.what());
			return false;
		}

		Log::Write("PyRuntime started");
		
		return true;
	}

	void PyRuntime::Close() {
		if (!s_InterpreterRunning) {
			Log::Error("PyRuntime is not running!");
			return;
		}

		py::finalize_interpreter();
		s_InterpreterRunning = false;

		Log::Write("PyRuntime stopped");
	}
}