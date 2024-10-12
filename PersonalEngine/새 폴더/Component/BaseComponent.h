#pragma once
#include "../RTTI/BaseRTTI.h"
#include <string>
class GameObject;

class BaseComponent :public BaseRTTI
{

	BaseComponent(const BaseComponent&) = delete;
public:
	BaseComponent() :own(nullptr) {}
	BaseComponent(GameObject* owner) : own(owner) {}
	static std::string GetType() { return "BaseComponent"; };
	virtual ~BaseComponent() = default;
	virtual void Update() = 0;
	virtual void LoadFromJson(const json& data) = 0;

	GameObject* own;
	GameObject* GetOwner() { return own; }
};
