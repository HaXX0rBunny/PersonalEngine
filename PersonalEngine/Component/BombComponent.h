#pragma once
#include "SpriteComponent.h"
#include "../Utility/InputProcess.h"

#include "LogicComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"


class BomnComp : public LogicComponent
{
	int BombCount;
	int LifeTime;
	int BombPower;
	int BombType;
public:
	void Update();
	void CreateBomb();
	const std::string& GetType() { "BombComp"; };
	void LoadFromJson(const json& data);

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateBomnComp();
};