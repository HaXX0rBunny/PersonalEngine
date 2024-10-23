#pragma once

#include <iostream>
namespace GSM
{
	class BaseLevel;
	class GameStateManager {
		static GameStateManager* Instance;

		BaseLevel* previousLevel;
		BaseLevel* currentLevel;

		bool isfirst= true;
		GameStateManager();
		GameStateManager(const GameStateManager& other) = delete;
		const GameStateManager& operator=(const GameStateManager& other) = delete;
		~GameStateManager();

	public:
		static GameStateManager* GetInstance()
		{
			if (Instance == nullptr)
			{
				Instance = new GameStateManager;

			}
			return Instance;
		}

		static void DeleteGSM();
		

		void Init();
		void Update();
		void Exit();
		//Function to change level
		void ChangeLevel(BaseLevel* newLvl);
		
		bool ShouldExit();
	};


};

