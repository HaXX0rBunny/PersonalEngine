#include "LogicComponent.h"
#include "../CManager/LogicManager.h"
LogicComponent::LogicComponent()
{
	LogicManager::Instance()->AddComponent(this);
}

LogicComponent::~LogicComponent()
{
	LogicManager::Instance()->RemoveComp(this);
}
