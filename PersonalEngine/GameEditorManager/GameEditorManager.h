#pragma once
#include"../Editor/MainMenu.h"
#include "../GameEditorManager/EditorInteractManager.h"
#include "../Utility/EngineState.h"
#include "../Editor/ProfilerMoniter.h"
#include "../Editor/TileEditor.h"
namespace GEM
{
	class BaseEditor;
	class GameEditorManager
	{
		static GameEditorManager* Instance;
		MainMenu* mainMenu =nullptr;
		TileEditor* tileEdit = nullptr;
		GameEditorManager();
		GameEditorManager(const GameEditorManager& other) = delete;
		const GameEditorManager& operator=(const GameEditorManager& other) = delete;
		~GameEditorManager();
	public:
		static GameEditorManager* GetInstance()
		{
			if (Instance == nullptr)
			{
				Instance = new GameEditorManager;
			}
			return Instance;
		}

		void DeleteGEM();

		void Init();
		void Update();
		void Exit();
	

	};
}