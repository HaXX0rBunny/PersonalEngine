#include "GraphicsComponent.h"
#include "../CManager/ComponentManager.h"


GraphicsComponent::GraphicsComponent(GameObject* owner)
    : BaseComponent(owner)
{
    ComponentManager<GraphicsComponent>::Instance()->AddComponent(this);
}

GraphicsComponent::~GraphicsComponent()
{
    ComponentManager<GraphicsComponent>::Instance()->RemoveComp(this);
}