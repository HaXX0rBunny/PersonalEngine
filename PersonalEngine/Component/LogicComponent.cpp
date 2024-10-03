#include "LogicComponent.h"
#include "../CManager/ComponentManager.h"
LogicComponent::LogicComponent()
{
	ComponentManager<LogicComponent>::Instance()->AddComponent(this);
}

LogicComponent::~LogicComponent()
{
	ComponentManager<LogicComponent>::Instance()->RemoveComp(this);
}
