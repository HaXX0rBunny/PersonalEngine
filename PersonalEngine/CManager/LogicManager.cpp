#include "LogicManager.h"

LogicManager* LogicManager::Instance_ = nullptr;  

LogicManager::~LogicManager()
{
    clear();
}

void LogicManager::clear()
{
    delete Instance_;
    Instance_ = nullptr;
}

LogicComponent* LogicManager::GetComponent(const std::string& str) const
{
    for (auto a : Component)
        if (a->GetType() == str)
            return a;
    return nullptr;
}

void LogicManager::AddComponent(LogicComponent* component)
{
    Component.push_back(component);
}

void LogicManager::RemoveComp(LogicComponent* component)
{
    Component.erase(std::find(Component.begin(), Component.end(), component));
}

void LogicManager::Update()
{
    for (auto it : Component)
    {
        it->Update();
    }
}
