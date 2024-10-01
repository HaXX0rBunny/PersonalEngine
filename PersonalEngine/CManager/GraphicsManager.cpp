#include "GraphicsManager.h"

GraphicsManager* GraphicsManager::Instance_ = nullptr;  

GraphicsManager::~GraphicsManager()
{
    clear();
}


void GraphicsManager::clear()
{
    delete Instance_;
    Instance_ = nullptr;
}

GraphicsComponent* GraphicsManager::GetComponent(const std::string& str) const
{
    for (auto a : Component)
        if (a->GetType() == str)
            return a;
    return nullptr;
}

void GraphicsManager::AddComponent(GraphicsComponent* component)
{
    Component.push_back(component);
}

void GraphicsManager::RemoveComp(GraphicsComponent* component)
{
    Component.erase(std::remove(Component.begin(), Component.end(), component), Component.end());
}

void GraphicsManager::Update()
{
    for (auto it : Component)
    {
        it->Update();
    }
}
