#pragma once
#include "EngineComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "../GameObject/GameObject.h"
class BlockComp :public LogicComponent
{
	bool moveAble;
	int fiber;
public:
	BlockComp(GameObject* owner);
	~BlockComp();
	void SetMove(const bool&);
	void Setfiber(const int&);
	void Update()override;
	void SpawnItem();
	void DestoryBlock();
	static std::string GetType()
	{
		return "BlockComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateBlockComp();

};