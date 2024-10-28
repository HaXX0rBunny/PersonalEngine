#include "GameEditorManager.h"
GEM::GameEditorManager* GEM::GameEditorManager::Instance = nullptr;
GEM::GameEditorManager::GameEditorManager()
{

}
GEM::GameEditorManager::~GameEditorManager()
{
}

void GEM::GameEditorManager::DeleteGEM()
{
	delete mainMenu;
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}

}

void GEM::GameEditorManager::Init()
{
	mainMenu = new MainMenu();

}

void GEM::GameEditorManager::Update()
{
	mainMenu->Update();
	EditorInteractManager::GetInstance()->Update();
}

void GEM::GameEditorManager::Exit()
{
}
