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
		// ������ ������Ʈ�� GameObject�� �߰��ϰ� ��ȯ
		BaseComponent* baseComp = dynamic_cast<BaseComponent*>(newComponent);
		if (dynamic_cast<BaseComponent*>(newComponent) != nullptr)
		{
			baseComp->own = this;
			Component[type]=baseComp;  // �� ������Ʈ�� �߰� (�ʿ� �����ϴ� ���� ����)

			return baseComp;  // �� ������Ʈ�� ��ȯ
		}
		else
		{
			// Ÿ�� ��ȯ ���� �� nullptr ��ȯ
			std::cerr << "Error: Failed to cast newComponent to BaseComponent." << std::endl;
			delete newComponent;
			return nullptr;
		}
	}

	// ������Ʈ�� �������� ���ϸ� nullptr ��ȯ
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

