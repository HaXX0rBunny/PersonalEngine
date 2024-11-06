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
	bool isRemote;
	bool isGrab;
	bool isKick;
	bool isImune;
	bool isCurse;

};
class PlayerComp : public LogicComponent
{
	bool isPlayerInside = true;  // 플레이어가 폭탄 범위 안에 있는지 체크
	bool canCollide = false;     // 충돌 가능 상태인지 체크
	PlayerStat state;
	float spin;
	float worldLimit;
	int flagDirection;
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
	const int& GetDirection();

	bool GetMode();
	void SetState(const ItemList&);
	static std::string GetType()
	{
		return "PlayerComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreatePlayerComp();
};