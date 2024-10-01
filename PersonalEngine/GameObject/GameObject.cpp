#include "GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Component/BaseComponent.h"


GameObject::GameObject()
{
	GameObjectManager::Instance()->AddObj(this);
}

GameObject::GameObject(BaseComponent* component)
{
	AddComponent(component);
}

GameObject::GameObject(const GameObject& other)
{
	CopyComponents(other);
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this != &other) {
		Clear();
		CopyComponents(other);
	}
	return *this;
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

void GameObject::CopyComponents(const GameObject& other)
{
	for (auto& comp : other.Component) {
		Component.insert({ comp.first, comp.second });
	}
}

