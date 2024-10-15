#include "GameObject.h"

#include "../Component/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../RTTI/Registry.h"
GameObject::GameObject()
{
	name = "";
	GameObjectManager::Instance()->AddObj(name,this);
}

GameObject::GameObject(std::string id)
{
	name = id;
	GameObjectManager::Instance()->AddObj(id,this);
}


GameObject::~GameObject()
{
	Clear();
}

std::map<std::string, BaseComponent*>& GameObject::AllComp()
{
	return Component;
}


void GameObject::RemoveComponent(const std::string& id)
{
	auto it = Component.find(id);
	if (it != Component.end())
	{
		delete it->second; 
		Component.erase(it);
	}
}

bool GameObject::HasComponent(const std::string& id) const
{

	auto it = Component.find(id);
	return it != Component.end();
}

std::map<std::string, BaseComponent*> GameObject::AllComponent()
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
		BaseComponent* baseComp = dynamic_cast<BaseComponent*>(newComponent);
		if (dynamic_cast<BaseComponent*>(newComponent) != nullptr)
		{
			baseComp->own = this;
			Component[type]=baseComp;  // 새 컴포넌트를 추가 (맵에 저장하는 역할 포함)

			return baseComp;  // 새 컴포넌트를 반환
		}
		else
		{
			// 타입 변환 실패 시 nullptr 반환
			std::cerr << "Error: Failed to cast newComponent to BaseComponent." << std::endl;
			delete newComponent;
			return nullptr;
		}
	}

	// 컴포넌트를 생성하지 못하면 nullptr 반환
	return nullptr;
}
void GameObject::Renamed(const std::string& re)
{
	name = re;
}
void GameObject::Clear()
{
	for (auto& comp : Component) {
		if (comp.second)
			delete comp.second;
	}
	Component.clear();
}

