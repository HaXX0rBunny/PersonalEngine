#pragma once
#include "EngineComponent.h"
#include "TransformComponent.h"
#include "../GameObject/GameObject.h"
#include "RigidbodyComponent.h"
#include "../Utility/InputProcess.h"
#include "../Utility/EngineState.h"
class PlayerComp : public EngineComponent
{
	float moveSpeed;
	float spin;
	float worldLimit;
	bool playMode;
public:
	PlayerComp(GameObject* owner);
	~PlayerComp();
	void Update() override;

	void SetMode(const bool& cb_in);
	bool GetMode();

	static std::string GetType()
	{
		return "PlayerComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateTransformComp();
};