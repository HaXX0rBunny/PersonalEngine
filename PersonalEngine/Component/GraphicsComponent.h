#pragma once
#include "BaseComponent.h"
#include <string>
class GameObject;

class GraphicsComponent : public BaseComponent
{
public:

	GraphicsComponent(GameObject* owner);
	~GraphicsComponent();
	virtual void LoadFromJson(const json& data) = 0;

	static std::string GetType()
	{
		return "GraphicsComponent";
	}
};