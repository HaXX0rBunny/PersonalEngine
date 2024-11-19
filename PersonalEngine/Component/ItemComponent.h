#pragma once
#include "LogicComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
enum ItemList {
	SpeedUp,
	KickUp,
	PowerUp,
	GrabUp,
	BombUp,
	Imune,
	RemoteUp,
	Curse,
	NotItem
};

struct ItemDropInfo {
	ItemList type;
	float dropChance;  // 0.0f ~ 100.0f
	std::string texturePath;
};

// 아이템 드롭 테이블 정의
const std::vector<ItemDropInfo> itemDropTable = {
	{ItemList::PowerUp, 30.0f, "Assets/PowerUp.png"},
	{ItemList::SpeedUp, 25.0f, "Assets/SpeedUp.png"},
	{ItemList::BombUp, 20.0f, "Assets/BombUp.png"},
	{ItemList::GrabUp, 10.0f, "Assets/GrabUp.png"},
	{ItemList::KickUp, 10.0f, "Assets/KickUp.png"},
	{ItemList::Imune, 3.0f, "Assets/Imune.png"},
	{ItemList::RemoteUp, 1.5f, "Assets/RemoteUp.png"},
	{ItemList::Curse, 0.5f, "Assets/Curse.png"}
};
class ItemComp : public LogicComponent
{
	ItemDropInfo ItemType;

public:
	ItemComp(GameObject* owner);
	~ItemComp();
	const ItemDropInfo& GetItemType() { return ItemType; };
	void setItem(const ItemDropInfo&);
	void Update() override;
	void DestroyItem();
	void LoadFromJson(const json& data);
	json SaveToJson() override;
	static BaseRTTI* CreateItemComp();
	static std::string GetType()
	{
		return "ItemComp";
	}

};