#include "EventManager.h"
#include <iostream>
// EventManager 생성자
EventManager::EventManager() {}

// EventManager 소멸자
EventManager::~EventManager() {
    while (!qp_entities.empty()) {
        delete qp_entities.front();
        qp_entities.pop();
    }
}
// 이벤트를 삭제
void EventManager::DelEvent(Event* event) {
    if (!qp_entities.empty()) {
        Event* frontEvent = qp_entities.front();
        if (frontEvent == event) {
            qp_entities.pop();
            delete event;  // 동적으로 생성된 이벤트 삭제
        }
    }
}

void EventManager::RegistEntity(Event* event, Entity* ep_RegistEntity) {
    // 이벤트에 엔티티 등록
    // mpp_eventRegistry는 Event*를 키로 하고, 관련된 Entity*의 벡터를 값으로 가짐
    mpp_eventRegistry[event].push_back(ep_RegistEntity);
}

void EventManager::UnregisterEntity(Event* event, Entity* ep_UnRegEntity) {
    // 이벤트에 등록된 엔티티 목록에서 해당 엔티티를 찾아 제거
    auto it = mpp_eventRegistry.find(event);
    if (it != mpp_eventRegistry.end()) {
        auto& entities = it->second;
        // 엔티티 목록에서 삭제
        entities.erase(std::remove(entities.begin(), entities.end(), ep_UnRegEntity), entities.end());

        // 만약 엔티티 목록이 비어 있으면 이벤트 자체도 삭제
        if (entities.empty()) {
            mpp_eventRegistry.erase(it);
        }
    }
}


// 큐에 있는 모든 이벤트를 디스패치
void EventManager::DispatchEvent() {
    std::vector<Event*> toDelete;
    while (!qp_entities.empty()) {
        Event* event = qp_entities.front();
        qp_entities.pop();

        // 이벤트가 등록된 엔티티들에게 디스패치
        std::cout << "Dispatching event: " << typeid(*event).name() << std::endl;

        // 이벤트를 각 엔티티에 전달
        if(event->src)
            event->src->OnEvent(event);
        if(event->dst)
            event->dst->OnEvent(event);
        toDelete.push_back(event);
    }
    for (Event* event : toDelete) {
        delete event;
    }
}
