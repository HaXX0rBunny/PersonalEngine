#pragma once
#include "../Component/EngineComponent.h"
#include <vector>
class EngineManager
{
    static EngineManager* Instance_;
    EngineManager() = default;
    std::vector<EngineComponent*> Component;
    ~EngineManager();
public:
    static EngineManager* Instance() {
        if (Instance_ == nullptr)
            Instance_ = new EngineManager;
        return Instance_;
    }
    static void clear();
    EngineComponent* GetComponent(const std::string& str) const;
    void AddComponent(EngineComponent* component);
    void RemoveComp(EngineComponent* component);
    void Update();
};
