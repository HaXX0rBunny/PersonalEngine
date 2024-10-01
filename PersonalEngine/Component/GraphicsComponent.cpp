#include "GraphicsComponent.h"
#include "../CManager/GraphicsManager.h"

GraphicsComponent::GraphicsComponent()
{
    GraphicsManager::Instance()->AddComponent(this);
}

GraphicsComponent::GraphicsComponent(GameObject* owner)
    : BaseComponent(owner)
{
    GraphicsManager::Instance()->AddComponent(this);
}

GraphicsComponent::~GraphicsComponent()
{
    GraphicsManager::Instance()->RemoveComp(this);
}