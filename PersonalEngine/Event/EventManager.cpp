#include "EventManager.h"
#include <iostream>
// EventManager ������
EventManager::EventManager() {}

// EventManager �Ҹ���
EventManager::~EventManager() {
    while (!qp_entities.empty()) {
        delete qp_entities.front();
        qp_entities.pop();
    }
}
// �̺�Ʈ�� ����
void EventManager::DelEvent(Event* event) {
    if (!qp_entities.empty()) {
        Event* frontEvent = qp_entities.front();
        if (frontEvent == event) {
            qp_entities.pop();
            delete event;  // �������� ������ �̺�Ʈ ����
        }
    }
}

void EventManager::RegistEntity(Event* event, Entity* ep_RegistEntity) {
    // �̺�Ʈ�� ��ƼƼ ���
    // mpp_eventRegistry�� Event*�� Ű�� �ϰ�, ���õ� Entity*�� ���͸� ������ ����
    mpp_eventRegistry[event].push_back(ep_RegistEntity);
}

void EventManager::UnregisterEntity(Event* event, Entity* ep_UnRegEntity) {
    // �̺�Ʈ�� ��ϵ� ��ƼƼ ��Ͽ��� �ش� ��ƼƼ�� ã�� ����
    auto it = mpp_eventRegistry.find(event);
    if (it != mpp_eventRegistry.end()) {
        auto& entities = it->second;
        // ��ƼƼ ��Ͽ��� ����
        entities.erase(std::remove(entities.begin(), entities.end(), ep_UnRegEntity), entities.end());

        // ���� ��ƼƼ ����� ��� ������ �̺�Ʈ ��ü�� ����
        if (entities.empty()) {
            mpp_eventRegistry.erase(it);
        }
    }
}


// ť�� �ִ� ��� �̺�Ʈ�� ����ġ
void EventManager::DispatchEvent() {
    std::vector<Event*> toDelete;
    while (!qp_entities.empty()) {
        Event* event = qp_entities.front();
        qp_entities.pop();

        // �̺�Ʈ�� ��ϵ� ��ƼƼ�鿡�� ����ġ
        std::cout << "Dispatching event: " << typeid(*event).name() << std::endl;

        // �̺�Ʈ�� �� ��ƼƼ�� ����
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
