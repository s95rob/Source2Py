#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

// pybind11 does some sketchy things that breaks the Source 2 SDK when compiling with MSVC
#ifdef _WIN32
	#undef _DEBUG
	#define _DEBUG 1
#endif