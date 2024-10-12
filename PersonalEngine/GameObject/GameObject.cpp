#include "GameObject.h"

#include "../Component/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../RTTI/Registry.h"
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




BaseComponent* GameObject::LoadComponent(const std::string& type)
{
	auto it = Component.find(type);
	if (it != Component.end())
	{
		return it->second;
	}
	BaseRTTI* newComponent = Registry::Instance()->FindAndCreate(type);
	if (newComponent != nullptr)
	{
		// 생성된 컴포넌트를 GameObject에 추가하고 반환
		AddComponent<BaseComponent>(static_cast<BaseComponent*>(newComponent));
		return static_cast<BaseComponent*>(newComponent);
	}

	return nullptr;
}

void GameObject::Clear()
{
	for (auto& comp : Component) {
		if (comp.second)
			delete comp.second;
	}
	Component.clear();
}

