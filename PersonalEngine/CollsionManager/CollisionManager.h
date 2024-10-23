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
    static CollisionManager* GetInstance() {
        static CollisionManager instance;
        return &instance;
    }
 
    void Update();
    // 충돌 컴포넌트 등록
    void RegisterCollisionComponent(CollisionComp* comp);
    // 충돌 컴포넌트 해제
    void UnregisterCollisionComponent(CollisionComp* comp);

    // 모든 충돌 체크
    void CheckAllCollisions();

};