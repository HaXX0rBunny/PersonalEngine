#include "CollisionEvent.h"
#include <iostream>
#include "../GameObject/GameObject.h"

CollisionEvent::CollisionEvent(Entity* src, Entity* dst) : Event(src, dst) {
    
}
