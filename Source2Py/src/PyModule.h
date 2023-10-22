// Include this _once_ in a source file to define Source2Py module

#pragma once

#include "PyAPI.h"
#include "PyInclude.h"

#include <igameevents.h>

PYBIND11_EMBEDDED_MODULE(Source2Py, m) {
	using namespace Source2Py;

	m.def("ServerPrint", &PyAPI::ConPrint);
	m.def("ClientPrint", &PyAPI::ClientConPrint);

	m.def("ServerCommand", &PyAPI::ServerCommand);
	m.def("ClientCommand", &PyAPI::ClientCommand);

	m.def("SetTimescale", &PyAPI::SetTimescale);

	py::class_<IGameEvent>(m, "GameEvent")
		.def("GetName", &IGameEvent::GetName)
		.def("GetID", &IGameEvent::GetID)
		.def("GetBool", &IGameEvent::GetBool)
		.def("GetInt", &IGameEvent::GetInt)
		.def("GetFloat", &IGameEvent::GetFloat)
		.def("GetString", &IGameEvent::GetString);
}