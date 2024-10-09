#pragma once
#include "BaseLevel.h"
class GameObject;
namespace Level
{
	class TestLevel :public GSM::BaseLevel
	{
		GameObject* testObj = nullptr;

	public:
	
		void Init() override;
		void Update() override;
		void Exit() override;

	};

}