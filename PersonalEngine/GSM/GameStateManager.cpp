#include "GameStateManager.h"
GSM::GameStateManager* GSM::GameStateManager::Instance = nullptr;
GSM::GameStateManager::GameStateManager()
{
}

GSM::GameStateManager::~GameStateManager()
{
}


void GSM::GameStateManager::DeleteGSM()
{
}

void GSM::GameStateManager::Init()
{
}

void GSM::GameStateManager::Update()
{
}

void GSM::GameStateManager::Exit()
{
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
}

bool GSM::GameStateManager::ShouldExit()
{
    return false;
}
