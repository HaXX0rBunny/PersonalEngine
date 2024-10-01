#pragma once
#include "../Component/LogicComponent.h"
#include <vector>
class LogicManager
{
    static LogicManager* Instance_;
    LogicManager() = default;
    std::vector<LogicComponent*> Component;
    ~LogicManager();
public:
    static LogicManager* Instance() {
        if (Instance_ == nullptr)
            Instance_ = new LogicManager;
        return Instance_;
    }
    static void clear();
    LogicComponent* GetComponent(const std::string& str) const;
    void AddComponent(LogicComponent* component);
    void RemoveComp(LogicComponent* component);
    void Update();
};
