#pragma once

#include <vector>
#include "../Component/CollisionComponent.h"
#include "CollisionEvent.h"

class CollisionManager {
private:
    // 모든 충돌 컴포넌트를 관리하는 벡터
    std::vector<CollisionComp*> collisionComponents;

    CollisionManager() {}  // 싱글톤 패턴을 사용하기 위해 private로 설정
    ~CollisionManager() = default;

public:
    // 싱글톤 인스턴스 가져오기
    static CollisionManager& GetInstance() {
        static CollisionManager instance;
        return instance;
    }
 
    // 충돌 컴포넌트 등록
    void RegisterCollisionComponent(CollisionComp* comp) {
        collisionComponents.push_back(comp);
    }

    // 충돌 컴포넌트 해제
    void UnregisterCollisionComponent(CollisionComp* comp) {
        collisionComponents.erase(std::remove(collisionComponents.begin(), collisionComponents.end(), comp), collisionComponents.end());
    }

    // 모든 충돌 체크
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