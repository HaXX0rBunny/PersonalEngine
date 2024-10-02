#include "GameObject.h"

#include "../Component/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject::GameObject()
{
	GameObjectManager::Instance()->AddObj(this);
}

GameObject::GameObject(std::string id)
{
	GameObjectManager::Instance()->AddObj(this, id);
}


GameObject::~GameObject()
{
	Clear();
}

std::map<std::string, BaseComponent*>& GameObject::AllComp()
{
	return Component;
}

void GameObject::Clear()
{
	for (auto& comp : Component) {
		delete comp.second;
	}
	Component.clear();
}

