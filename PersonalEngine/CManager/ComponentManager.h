#pragma once
#include "../Component/BaseComponent.h"
#include "../Component/GraphicsComponent.h"
#include "../Component/LogicComponent.h"
#include "../Component/EngineComponent.h"

#include <iostream>
#include <vector>
#include <list>
#include <cassert>  // For static_assert

template <typename T>
class ComponentManager
{
    // Ensure T is derived from BaseComponent

    static ComponentManager* Instance_;
    std::vector<T* > Component;
    std::vector<T* > PendingComp;
    std::vector<T* > PendingRemove;
    ComponentManager();

    ~ComponentManager();

public:
    static ComponentManager* Instance() {
        if (Instance_ == nullptr)
        {
            Instance_ = new ComponentManager;
        }
        return Instance_;
    }

    void Clear();

    void DestroyInstance();

    T* GetComponent(const std::string& str) const;

    void AddComponent(T* component);

    void RemoveComp(T* component);

    void Update();
};



#include "ComponentManager.inl"
