#pragma once

#include "PyAPI.h"

#include <pybind11/embed.h>
namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(Source2Py, m) {
	using namespace Source2Py;

	m.def("Print", &PyAPI::ConPrint);
}