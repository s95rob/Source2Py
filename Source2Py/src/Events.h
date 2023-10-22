#pragma once

#include "Source2Py.h"

#include <igameevents.h>
#include <vector>

namespace Source2Py {

	extern Source2PyPlugin g_Source2PyPlugin;

	class EventListener;

	class EventService {
	public:
		static bool Init();
		static bool LoadEventsFromFile(const std::string& filepath);
		static void UnloadEvents();

	private:
		
	};

	class EventListener : public IGameEventListener2 {
	public:
		EventListener(const std::string& eventName) : m_EventName(eventName) {}

		// FireEvent is called by EventManager if event just occurred
		// KeyValue memory will be freed by manager if not needed anymore
		void FireGameEvent(IGameEvent* event) override {
			g_Source2PyPlugin.Hook_FireGameEvent(event); // Dispatch event to g_Source2PyPlugin (to be then dispatched to Python)
		}

		const char* GetEventName() const { return m_EventName.c_str(); }

	private:
		std::string m_EventName;
	};

}