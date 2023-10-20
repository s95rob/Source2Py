#pragma once

#include "PyAPI.h"

#include <pybind11/embed.h>
namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(Source2Py, m) {
	using namespace Source2Py;

	m.def("Print", &PyAPI::ConPrint);
	m.def("ClientPrint", &PyAPI::ClientConPrint);

	m.def("ServerCommand", &PyAPI::ServerCommand);
	m.def("ClientCommand", &PyAPI::ClientCommand);

	m.def("SetTimescale", &PyAPI::SetTimescale);
}