#pragma once

#include "Log.h"
#include "PyInclude.h"

namespace Source2Py {

	class PyRuntime {
	public:
		static bool Init();
		static void Close();

		/*
		@brief Run Python object method. Releases object on exception. 
		@param[in] object The Python object to reference
		@param[in] function The method to call
		@param[in] args Arguments to pass to method
		@returns True on success
		*/
		template <typename ... Args>
		static bool ExecuteObjectMethod(py::object& object, const char* function, Args&& ... args) {
			if (object.ptr() == nullptr)
				return false;

			try {
				if (py::hasattr(object, function))
					object.attr(function)(object, std::forward<Args>(args)...);
			}
			catch (py::error_already_set& e) {
				Log::Write("PYTHON ERROR:\n" + std::string(e.what()));
				object.release();
				return false;
			}

			return true;
		}

	private:
		static bool s_InterpreterRunning;
	};
}