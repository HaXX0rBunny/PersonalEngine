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
    static CollisionManager* GetInstance() {
        static CollisionManager instance;
        return &instance;
    }
 
    void Update();
    // �浹 ������Ʈ ���
    void RegisterCollisionComponent(CollisionComp* comp);
    // �浹 ������Ʈ ����
    void UnregisterCollisionComponent(CollisionComp* comp);

    // ��� �浹 üũ
    void CheckAllCollisions();

};