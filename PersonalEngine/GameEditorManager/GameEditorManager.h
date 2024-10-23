#pragma once
#include"../Editor/MainMenu.h"


namespace GEM
{
	class BaseEditor;
	class GameEditorManager
	{
		static GameEditorManager* Instance;
		MainMenu* mainMenu =nullptr;
	
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