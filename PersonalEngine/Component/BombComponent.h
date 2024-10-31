#pragma once
#include "SpriteComponent.h"
#include "../Utility/InputProcess.h"

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
class BombComp : public BaseComponent
{
	int BombCount;
	int LifeTime;
	int BombPower;
	BombType Bombtype;
	BombComp(GameObject* owner);
	~BombComp();
public:
	void Update();
	void CreateBomb();
	const std::string& GetType() { "BombComp"; };
	void LoadFromJson(const json& data);
	void Explosion();
	void BombEffect();
	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateBomnComp();
};