#pragma once
#include "SpriteComponent.h"
#include "../Utility/InputProcess.h"
#include "../Utility/Time.h"
#include "LogicComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "../Utility/Time.h"
#include "../CManager/BombManager.h"
enum BombType {
	Default,
	Timebomb,
	Dynamite,
	Boobytrap,
	melloondago,
};
class BombComp : public LogicComponent
{
	double startTime;  // 생성 시점 저장
	int BombCount;
	float LifeTime;
	bool isExploded;
	int BombPower;
	BombType Bombtype;

public:
	BombComp(GameObject* owner);
	~BombComp();
	void Update()override;
	void Explode();

	static std::string GetType() { return "BombComp"; };
	void LoadFromJson(const json& data)override;
	void Explosion();
	void BombEffect();
	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateBomnComp();
};