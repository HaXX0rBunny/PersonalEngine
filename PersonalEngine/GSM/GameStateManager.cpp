#include "GameStateManager.h"
#include "BaseLevel.h"
GSM::GameStateManager* GSM::GameStateManager::Instance = nullptr;

GSM::GameStateManager::GameStateManager():previousLevel(nullptr), currentLevel(nullptr)
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
}

void GSM::GameStateManager::Exit()
{
    if (currentLevel)
    {
        currentLevel->Exit();
    }
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
