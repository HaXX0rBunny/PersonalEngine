#pragma once
#include "../Component/BaseComponent.h"
#include <vector>
#include <memory>  // For smart pointers if needed
#include <cassert>  // For static_assert

template <typename T>
class ComponentManager
{
    // Ensure T is derived from BaseComponent
    static_assert(std::is_base_of<BaseComponent, T>::value, "T must inherit from BaseComponent");

    static ComponentManager* Instance_;


    ComponentManager() = default;
    std::vector<T* > Component;
    ~ComponentManager();

public:
    static ComponentManager* Instance() {
        if (Instance_ == nullptr)
        {
            Instance_ = new ComponentManager;
    
        }
        return Instance_;
    }

    static void Clear();

    void DestroyInstance();

    T* GetComponent(const std::string& str) const;

    void AddComponent(T* component);

    void RemoveComp(T* component);

    void Update();
};





#include "ComponentManager.inl"
