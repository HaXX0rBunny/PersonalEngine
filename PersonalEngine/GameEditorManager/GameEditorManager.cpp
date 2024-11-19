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
	DEBUG_PROFILER_START("Editor");
	ProfilerMoniter::GetInstance()->Update();
	DEBUG_PROFILER_END;
	if (Keystate::keystateF5 == GL_TRUE)
		EditorInteractManager::GetInstance()->selectedObject = nullptr;
	mainMenu->UpdateEditorState();
	if (EngineState::engineState_ == EngineMode::Editor)
	{
		mainMenu->Update();
		EditorInteractManager::GetInstance()->Update();

	}

}

void GEM::GameEditorManager::Exit()
{
}
