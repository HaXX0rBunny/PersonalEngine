#pragma once

#include <queue>
#include <map>
#include <list>
#include "Event.h"
#include "Entity.h"

class EventManager {
    // 이벤트 큐: 이벤트 객체를 저장하는 큐
    std::queue<Event*> qp_entities;

    // 이벤트 레지스트리: 이벤트와 관련된 엔티티들 관리
    std::map<Event*, std::list<Entity*>> mpp_eventRegistry;

    EventManager();  // 생성자
    EventManager(const EventManager& other) = delete;  // 복사 생성자 금지
    const EventManager& operator=(const EventManager& other) = delete;  // 대입 연산자 금지
    ~EventManager();  // 소멸자

public:
    static EventManager* GetInstance() {
        static EventManager Instance;  // 싱글톤 패턴 사용
        return &Instance;
    }

    // 이벤트 추가 및 삭제
    template <typename T>
    void AddEvent(Entity* src, Entity* dst);
    void DelEvent(Event* event);

    // 엔티티 등록 및 해제
    void RegistEntity(Event* event, Entity* ep_RegistEntity);
    void UnregisterEntity(Event* event, Entity* ep_UnRegEntity);

    // 이벤트 디스패치
    void DispatchEvent();
};

// 템플릿 함수 구현
template <typename T>
void EventManager::AddEvent(Entity* src, Entity* dst) {
    if (dst != nullptr) {
        // dst가 유효한 경우 이벤트 생성 후 큐에 추가
        Event* event = new T(src, dst);
        qp_entities.push(event);
    }
    else {
   
    }
}
