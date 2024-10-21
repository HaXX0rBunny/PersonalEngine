#pragma once
#include "BaseComponent.h"
#include <string>
class GameObject;

class EngineComponent : public BaseComponent
{
public:

	EngineComponent(GameObject* owner);
	~EngineComponent();
	virtual void LoadFromJson(const json& data) = 0;
	
	static std::string GetType()
	{
		return "EngineComponent";
	}
};
