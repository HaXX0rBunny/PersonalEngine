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
		// ������ ������Ʈ�� GameObject�� �߰��ϰ� ��ȯ
		BaseComponent* baseComp = dynamic_cast<BaseComponent*>(newComponent);
		if (baseComp != nullptr)
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
void GameObject::Clear()
{
	for (auto& comp : Component) {
		if (comp.second)
			delete comp.second;
	}
	Component.clear();
}

