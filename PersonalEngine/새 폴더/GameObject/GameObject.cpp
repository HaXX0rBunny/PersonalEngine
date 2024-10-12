#include "GameObject.h"

#include "../Component/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject::GameObject()
{
	name = "";
	GameObjectManager::Instance()->AddObj(this);
}

GameObject::GameObject(std::string id)
{
	name = id;
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
		if (comp.second)
			delete comp.second;
	}
	Component.clear();
}

