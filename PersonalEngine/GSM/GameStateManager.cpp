#include "GameStateManager.h"
#include "../Level/BaseLevel.h"
#include "../CManager/ComponentManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../RTTI/Registry.h"
#include "../Camera/Camera.h"
#include "../CollsionManager/CollisionManager.h"
#include "../Event/EventManager.h"
#include "../CManager/BombManager.h"
#include "../CollsionManager/CollisionManager.h"
GSM::GameStateManager* GSM::GameStateManager::Instance = nullptr;
GSM::GameStateManager::GameStateManager() :previousLevel(nullptr), currentLevel(nullptr)
{
}

GSM::GameStateManager::~GameStateManager()
{
	if (previousLevel)
		delete previousLevel;
	if (currentLevel)
		delete currentLevel;
}


void GSM::GameStateManager::DeleteGSM()
{
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void GSM::GameStateManager::Init()
{
	if (currentLevel)
	{
		currentLevel->Init();
	}
}

void GSM::GameStateManager::Update()
{




	if (currentLevel)
	{
		currentLevel->Update();
	}
	if (EngineState::engineState_ == Play)
	{
		//BombManager::GetInstance()->Update();
		ComponentManager<LogicComponent>::Instance()->Update();
		DEBUG_PROFILER_START("Collision");
		CollisionManager::GetInstance()->Update();
		DEBUG_PROFILER_END;
		DEBUG_PROFILER_START("Event");
		EventManager::GetInstance()->DispatchEvent();
		DEBUG_PROFILER_END;
	}
	DEBUG_PROFILER_START("Camera");
	Camera::GetInstance()->Update();
	DEBUG_PROFILER_END;
	ComponentManager<EngineComponent>::Instance()->Update();
	DEBUG_PROFILER_START("Grapics");
	ComponentManager<GraphicsComponent>::Instance()->Update();
	DEBUG_PROFILER_END;
}

void GSM::GameStateManager::Exit()
{
	if (currentLevel)
	{
		currentLevel->Exit();
	}
	GameObjectManager::Instance()->DestroyThis();
	/*delete first Because When the game object manager is destroyed,
	all game objects are deleted through the Clear() method (GameObjectManager).
	During this process, the components owned by each object are also deleted.
	If I delete the component manager first, 
	the component manager will be deleted even though the components may still exist, 
	so the game object will not be able to access the component when it is deleted.
	This may result in memory leaks or abnormal behavior.*/
	//BombManager::GetInstance()->DestroyInstance();
	ComponentManager<LogicComponent>::Instance()->DestroyInstance();
	ComponentManager<GraphicsComponent>::Instance()->DestroyInstance();  // Add this
	ComponentManager<EngineComponent>::Instance()->DestroyInstance();
	Registry::Instance()->Delete();
	ResourceManager::GetInstance()->Clear();
	
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
	if (isfirst)
	{
		currentLevel = newLvl;
		Init();
		isfirst = false;
	
	}
	else
	{
		if (previousLevel)
			delete previousLevel;
		previousLevel = currentLevel;
		Exit();
		currentLevel = newLvl;
		Init();
	}
}


bool GSM::GameStateManager::ShouldExit()
{
	return currentLevel == nullptr;
}
