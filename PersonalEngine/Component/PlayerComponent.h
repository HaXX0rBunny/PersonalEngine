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
enum PlayerNumber {
	Player1,
	Player2,
	Player3,
	Player4
};

struct PlayerStat {
	int moveSpeed;
	int BombPower;
	int BombCount;
	bool isGrab;
	bool isKick;
	bool isImune;

};
class PlayerComp : public LogicComponent
{
	PlayerStat state;
	float spin;
	float worldLimit;
	bool playMode;
	bool isColliding = false;
	PlayerNumber Player;
public:
	
	PlayerComp(GameObject* owner);
	~PlayerComp();
	void PlaceBomb();
	void Update() override;
	void SetCollisionState(bool state);
	void SetMode(const bool& cb_in);
	void SetPlayer(const PlayerNumber&);
	void Player_1_Keymap();
	void Player_2_Keymap();
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