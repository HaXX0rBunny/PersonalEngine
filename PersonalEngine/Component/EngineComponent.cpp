#include "EngineComponent.h"
#include "../CManager/ComponentManager.h"


EngineComponent::EngineComponent(GameObject* owner)
	: BaseComponent(owner)
{
	ComponentManager<EngineComponent>::Instance()->AddComponent(this);
}

EngineComponent::~EngineComponent()
{
	ComponentManager<EngineComponent>::Instance()->RemoveComp(this);
}
