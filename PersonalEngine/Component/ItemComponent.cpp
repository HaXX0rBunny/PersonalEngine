#include "ItemComponent.h"

ItemComp::ItemComp(GameObject* owner):LogicComponent(owner)
{
}

ItemComp::~ItemComp()
{
}


void ItemComp::setItem(const ItemDropInfo& cs_in)
{
	ItemType = cs_in;
}

void ItemComp::Update()
{
}

void ItemComp::DestroyItem()
{
	GameObjectManager::Instance()->RemoveObj(own->GetName());
}

void ItemComp::LoadFromJson(const json& data)
{
}

json ItemComp::SaveToJson()
{
	return json();
}

BaseRTTI* ItemComp::CreateItemComp()
{
	return nullptr;
}
