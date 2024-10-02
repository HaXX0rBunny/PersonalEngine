
#pragma once
#include "../Component/BaseComponent.h"
#include <vector>
class ComponentManager
{
    static ComponentManager* Instance_;
    ComponentManager() = default;
    std::vector<ComponentManager*> Component;
    ~ComponentManager();
public:
    static ComponentManager* Instance() {
        if (Instance_ == nullptr)
            Instance_ = new ComponentManager;
        return Instance_;
    }
    static void Clear();
    template <typename T>
    T* GetComponent(const std::string& str) const;
    template <typename T>
    void AddComponent(T* component);
    template <typename T>
    void RemoveComp(T* component);
    template <typename T>
    void Update();
    //BaseComponent* GetComponent(const std::string& str) const;
    //void AddComponent(BaseComponent* component);
    //void RemoveComp(BaseComponent* component);
 
};

template<typename T>
inline T* ComponentManager::GetComponent(const std::string& str) const
{
    for (auto a : Component)
        if (a->GetType() == str)
            return a;
    return nullptr;
}

template<typename T>
inline void ComponentManager::AddComponent(T* component)
{
}

template<typename T>
inline void ComponentManager::RemoveComp(T* component)
{
}

template<typename T>
inline void ComponentManager::Update()
{
}
