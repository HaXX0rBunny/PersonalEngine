#pragma once

#include <vector>
#include "../Component/CollisionComponent.h"
#include "CollisionEvent.h"

class CollisionManager {
private:
    // ��� �浹 ������Ʈ�� �����ϴ� ����
    std::vector<CollisionComp*> collisionComponents;

    CollisionManager() {}  // �̱��� ������ ����ϱ� ���� private�� ����
    ~CollisionManager() = default;

public:
    // �̱��� �ν��Ͻ� ��������
    static CollisionManager& GetInstance() {
        static CollisionManager instance;
        return instance;
    }
 
    // �浹 ������Ʈ ���
    void RegisterCollisionComponent(CollisionComp* comp) {
        collisionComponents.push_back(comp);
    }

    // �浹 ������Ʈ ����
    void UnregisterCollisionComponent(CollisionComp* comp) {
        collisionComponents.erase(std::remove(collisionComponents.begin(), collisionComponents.end(), comp), collisionComponents.end());
    }

    // ��� �浹 üũ
    void CheckAllCollisions() {
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
};