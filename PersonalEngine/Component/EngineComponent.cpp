#include "EngineComponent.h"
#include "../CManager/ComponentManager.h"

EngineComponent::EngineComponent()
{
	ComponentManager<EngineComponent>::Instance()->AddComponent(this);
}

EngineComponent::~EngineComponent()
{
	ComponentManager<EngineComponent>::Instance()->RemoveComp(this);
}
