#pragma once
#include "../GameObject/GameObject.h"
#include "TransformComponent.h"
#include "EngineComponent.h"
#include "../Utility/Time.h"
#include <algorithm>
#include <glm.hpp>

#include <gtc/type_ptr.hpp>
#define EPSILON	0.00001f
class RigidbodyComp : public EngineComponent
{
	float drag = 0.5f;
	glm::vec2 Velocity;
	glm::vec2 MaxVelocity;
	bool CheckEpsilon(float v, float Ep = EPSILON);


public:

	RigidbodyComp(GameObject* owner);

	//void Addvelocity(const AEVec2& otherVec);
	void AddVelocity(float x, float y);
	glm::vec2 GetVelocity();
	void SetVelocity(float x, float y);
	void ClearVelocity();
	void Clamp(const float& cf_velocity, const float& cf_min, const float& cf_max);
	
	void Update() override;
	static std::string GetType()
	{
		return "RigidbodyComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	static BaseRTTI* CreateRigidbodyComp();
};