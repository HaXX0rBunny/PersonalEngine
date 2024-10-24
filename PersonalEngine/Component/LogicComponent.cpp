#include "LogicComponent.h"
#include "../CManager/ComponentManager.h"

LogicComponent::LogicComponent(GameObject* owner) 
	: BaseComponent(owner)
{
	ComponentManager<LogicComponent>::Instance()->AddComponent(this);
}

LogicComponent::~LogicComponent()
{
	ComponentManager<LogicComponent>::Instance()->RemoveComp(this);
}
