#include "BlockComponent.h"
#include <random>
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

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 100.0f);

	// 아이템 드롭 확률 계산
	float randomValue = dis(gen);
	float accumulatedChance = 0.0f;

	// 아이템 드롭 여부 결정 (전체 50% 확률)
	if (randomValue > 50.0f) {
		return; // 아이템을 드롭하지 않음
	}
	randomValue = dis(gen);	
	const ItemDropInfo* selectedItem = nullptr;

	for (const auto& item : itemDropTable)
	{
		accumulatedChance += item.dropChance;
		if (randomValue <= accumulatedChance)
		{
			selectedItem = &item;
			break;
		}
	}

	static int ItemCounter = 0;
	std::string ItemName = "Item_" + std::to_string(ItemCounter++);
	GameObject* Item = new GameObject(ItemName);
	Item->ObjectTag = GameObject::Tag::Item;

	SpriteComp * ItemSprite=Item->AddComponent<SpriteComp>();
	TransformComp* ItemTrans = Item->AddComponent<TransformComp>();
	ItemSprite->SetTexture();
	TransformComp* wonTrans = own->GetComponent<TransformComp>();
	ItemTrans->SetPos(wonTrans->GetPos());
	ItemTrans->SetScale(wonTrans->GetScale());
	CollisionComp* ItemCollision = Item->AddComponent<CollisionComp>();
	ItemComp* itemComp = Item->AddComponent<ItemComp>();
	itemComp->setItem(*selectedItem);

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
