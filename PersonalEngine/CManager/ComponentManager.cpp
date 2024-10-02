#include "ComponentManager.h"
ComponentManager* ComponentManager::Instance_ = nullptr;
ComponentManager::~ComponentManager()
{
	Clear();
}

void ComponentManager::Clear()
{
	if (Instance_)
	{
		delete Instance_;
		Instance_ = nullptr;
	}
}


