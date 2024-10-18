#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include "Event.h"
#include "Entity.h"
class EventManager
{
	std::map<Event*, std::vector<Entity*>> mpp_eventRegistry;
	std::queue<Event*> qp_entities;

	EventManager();
		EventManager(const EventManager& other) = delete;
	const EventManager& operator=(const EventManager& other) = delete;
	~EventManager();
	
public:
	static EventManager* GetInstance() {
		static EventManager Instance; 
		return &Instance;  
	}
	template <typename T>
	void AddEvent();
	void DelEvent();


	void RegistEntity(Entity* ep_RegistEntity);
	void UnregisterEntity(Entity* ep_UnRegEntity);


	void DispatchEvent();

	//Interface:
	//Add an event (event*) this are pointers to dynamic memory, called as the following: AddEvent(new Event);
	// 
	// templated fn:
	//		Register entities to a certain event TYPE
	//		Unregister entities to a certain event TYPE
	//
	// DispatchAllEvents
	//

	//delete undispatched events if any on destructor

};

template<typename T>
inline void EventManager::AddEvent()
{
}
