#include "GameStateManager.h"
#include "../Level/BaseLevel.h"
#include "../CManager/ComponentManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../RTTI/Registry.h"
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
	ComponentManager<LogicComponent>::Instance()->Update();
	ComponentManager<EngineComponent>::Instance()->Update();
	if (currentLevel)
	{
		currentLevel->Update();
	}
	ComponentManager<GraphicsComponent>::Instance()->Update();
}

void GSM::GameStateManager::Exit()
{
	if (currentLevel)
	{
		currentLevel->Exit();
	}

	ResourceManager::GetInstance()->Clear();
	ComponentManager<LogicComponent>::Instance()->DestroyInstance();
	ComponentManager<GraphicsComponent>::Instance()->DestroyInstance();  // Add this
	ComponentManager<EngineComponent>::Instance()->DestroyInstance();
	Registry::Instance()->Delete();
	GameObjectManager::Instance()->DestroyThis();
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
	if (previousLevel)
		delete previousLevel;
	previousLevel = currentLevel;
	Exit();
	currentLevel = newLvl;
	Init();
}


bool GSM::GameStateManager::ShouldExit()
{
	return currentLevel == nullptr;
}
