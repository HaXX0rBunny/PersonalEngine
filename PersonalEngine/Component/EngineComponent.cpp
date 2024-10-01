#include "EngineComponent.h"
#include "../CManager/EngineManager.h"

EngineComponent::EngineComponent()
{
	EngineManager::Instance()->AddComponent(this);
}

EngineComponent::~EngineComponent()
{
	EngineManager::Instance()->RemoveComp(this);
}
