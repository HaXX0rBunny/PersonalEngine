#include "BlockComponent.h"

BlockComp::BlockComp(GameObject* owner):LogicComponent(owner)
{
	own->ObjectTag = GameObject::Tag::Block;
	moveAble = false;
	fiber = 1;
}

BlockComp::~BlockComp()
{
}

void BlockComp::SetMove(const bool& cb_in)
{
	moveAble = cb_in;
}

void BlockComp::Setfiber(const int& ci_in)
{
	fiber = ci_in;
}

void BlockComp::Update()
{
	
}

void BlockComp::SpawnItem()
{
	GameObject* Item = new GameObject("Item");
	Item->ObjectTag = GameObject::Tag::Item;
	Item->ItemType = ItemList::PowerUp;
	SpriteComp * ItemSprite=Item->AddComponent<SpriteComp>();
	TransformComp* ItemTrans = Item->AddComponent<TransformComp>();
	ItemSprite->SetTexture();
	TransformComp* wonTrans = own->GetComponent<TransformComp>();
	ItemTrans->SetPos(wonTrans->GetPos());
	ItemTrans->SetScale(wonTrans->GetScale());
	CollisionComp* ItemCollision = Item->AddComponent<CollisionComp>();
}

void BlockComp::DestoryBlock()
{
	SpawnItem();
	GameObjectManager::Instance()->RemoveObj(own->GetName());
}

void BlockComp::LoadFromJson(const json& data)
{
	auto compData = data.find("CompData");

	if (compData != data.end())
	{
		auto ma = compData->find("moveAble");
		moveAble = ma->begin().value();

		auto fi = compData->find("fiber");
		fiber = fi->begin().value();
	}
}

json BlockComp::SaveToJson()
{
	json data;
	data["Type"] = GetType();
	json compData;
	compData["moveAble"] = moveAble;
	compData["fiber"] = fiber;

	data["CompData"] = compData;
	return data;
}

BaseRTTI* BlockComp::CreateBlockComp()
{
	GameObject* lastObj = GameObjectManager::Instance()->GetLastObj();
	if (lastObj == nullptr) {

		return nullptr;  // 혹은 적절한 예외 처리
	}

	BaseRTTI* out = new BlockComp(lastObj);

	return out;
}
