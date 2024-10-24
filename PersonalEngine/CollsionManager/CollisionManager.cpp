#include "CollisionManager.h"

void CollisionManager::RegisterCollisionComponent(CollisionComp* comp)
{
    {
        collisionComponents.push_back(comp);
    }
}

void CollisionManager::UnregisterCollisionComponent(CollisionComp* comp)
{
    
        collisionComponents.erase(std::remove(collisionComponents.begin(), collisionComponents.end(), comp), collisionComponents.end());
    
}

void CollisionManager::CheckAllCollisions() {
    for (size_t i = 0; i < collisionComponents.size(); ++i) {
        for (size_t j = i + 1; j < collisionComponents.size(); ++j) {
            CollisionComp* comp1 = collisionComponents[i];
            CollisionComp* comp2 = collisionComponents[j];

            if (comp1->CheckCollision(comp2)) {
                EventManager::GetInstance()->AddEvent<CollisionEvent>(comp1, comp2);
            }
        }
    }
}
void CollisionManager::Update()
{
    CheckAllCollisions();
}