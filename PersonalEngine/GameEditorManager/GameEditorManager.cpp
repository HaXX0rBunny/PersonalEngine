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

	delete tileEdit;
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}

}

void GEM::GameEditorManager::Init()
{
	mainMenu = new MainMenu();
	tileEdit = new TileEditor();
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
		tileEdit->Update();
		mainMenu->Update();
		if(!tileEdit->GetState())
			EditorInteractManager::GetInstance()->Update();
	}

}

void GEM::GameEditorManager::Exit()
{
}
