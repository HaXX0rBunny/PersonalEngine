#pragma once

#include <queue>
#include <map>
#include <list>
#include "Event.h"
#include "Entity.h"

class EventManager {
    // �̺�Ʈ ť: �̺�Ʈ ��ü�� �����ϴ� ť
    std::queue<Event*> qp_entities;

    // �̺�Ʈ ������Ʈ��: �̺�Ʈ�� ���õ� ��ƼƼ�� ����
    std::map<Event*, std::list<Entity*>> mpp_eventRegistry;

    EventManager();  // ������
    EventManager(const EventManager& other) = delete;  // ���� ������ ����
    const EventManager& operator=(const EventManager& other) = delete;  // ���� ������ ����
    ~EventManager();  // �Ҹ���

public:
    static EventManager* GetInstance() {
        static EventManager Instance;  // �̱��� ���� ���
        return &Instance;
    }

    // �̺�Ʈ �߰� �� ����
    template <typename T>
    void AddEvent(Entity* src, Entity* dst);
    void DelEvent(Event* event);

    // ��ƼƼ ��� �� ����
    void RegistEntity(Event* event, Entity* ep_RegistEntity);
    void UnregisterEntity(Event* event, Entity* ep_UnRegEntity);

    // �̺�Ʈ ����ġ
    void DispatchEvent();
};

// ���ø� �Լ� ����
template <typename T>
void EventManager::AddEvent(Entity* src, Entity* dst) {
    if (dst != nullptr) {
        // dst�� ��ȿ�� ��� �̺�Ʈ ���� �� ť�� �߰�
        Event* event = new T(src, dst);
        qp_entities.push(event);
    }
    else {
   
    }
}
