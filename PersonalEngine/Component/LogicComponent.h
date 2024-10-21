#pragma once
#include "BaseComponent.h"
#include <string>
class GameObject;

class LogicComponent : public BaseComponent
{
public:
	LogicComponent(GameObject* owner);
	~LogicComponent();
	virtual void LoadFromJson(const json& data) = 0;
	static std::string GetType()
	{
		return "LogicComponent";
	}
};
