#pragma once
#include "SpriteComponent.h"
#include "BombComponent.h"
#include "LogicComponent.h"
#include "TransformComponent.h"
#include "../GameObject/GameObject.h"
#include "RigidbodyComponent.h"
#include "../Utility/InputProcess.h"
#include "../Utility/EngineState.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Camera/Camera.h"
#include "CollisionComponent.h"
#include "../Utility/Profiler.h"
class PlayerComp : public LogicComponent
{
	float moveSpeed;
	float spin;
	float worldLimit;
	bool playMode;
	bool isColliding = false;
public:
	PlayerComp(GameObject* owner);
	~PlayerComp();
	void PlaceBomb();
	void Update() override;
	void SetCollisionState(bool state);
	void SetMode(const bool& cb_in);
	bool GetMode();

	static std::string GetType()
	{
		return "PlayerComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreatePlayerComp();
};