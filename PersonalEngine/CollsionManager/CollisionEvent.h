#pragma once
#include "../Event/Event.h"
#include "../GameObject/GameObject.h"

class CollisionEvent : public Event {
public:
    CollisionEvent(Entity* src, Entity* dst);

};