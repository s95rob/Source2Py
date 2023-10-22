#include "Events.h"
#include "Utility.h"

#include <vector>
#include <fstream>
#include <igameevents.h>
#include <eiface.h>

#define EVENTLISTENER_SLOTS 300 // todo: remove

namespace Source2Py {

	extern IGameEventManager2* gameevents;
	extern IServerGameDLL* server;

	std::vector<EventListener> eventListeners;

	bool EventService::Init() {
		gameevents = static_cast<IGameEventManager2*>(CallVFunc<IToolGameEventAPI*, 91>(server)); // get interface from ISource2Server vtable (func signature incomplete)
		if (!gameevents) {
			Log::Write("Failed to load IGameEventManager2!");
			return false;
		}
		
		Log::Write("IGameEventManager2 @ 0x" + AddrToString(static_cast<void*>(gameevents)));
		Log::Write("EventService initialized");
		return true;
	}

	bool EventService::LoadEventsFromFile(const std::string& filepath) {
		std::ifstream eventsFile(filepath);

		if (eventsFile.fail()) {
			Log::Error("Failed to load events file: " + filepath);
			return false;
		}

		// Keep the EventListeners memory block from jumping around
		// todo: precalculate the exact vector size needed. this is a crash waiting to happen if events
		eventListeners.reserve(EVENTLISTENER_SLOTS);
		Log::Write("Reserved " + std::to_string(EVENTLISTENER_SLOTS) + " EventListener slots (" + std::to_string(sizeof(EventListener) * EVENTLISTENER_SLOTS) + " bytes)");

		std::string line;
		while (std::getline(eventsFile, line)) {
			// ignore comments
			if (line[0] == '#' || line[0] == ';' || line.empty())
				continue;

			eventListeners.push_back(line);
			EventListener& listener = eventListeners.back();

			if (!gameevents->AddListener(&listener, listener.GetEventName(), true)) {
				Log::Write("Failed to add EventListener: " + std::string(listener.GetEventName()));
				eventListeners.pop_back();
			}
		}

		Log::Write("Added " + std::to_string(eventListeners.size()) + " EventListeners");
		if (eventListeners.size() > EVENTLISTENER_SLOTS) // todo: remove
			Log::Error("Added more EventListeners than reserved, prepare for crash!");

		return true;
	}

	void EventService::UnloadEvents() {
		for (auto& listener : eventListeners)
			gameevents->RemoveListener(&listener);

		Log::Write("Unloaded all EventListeners");
	}
}