#pragma once
#include <list>
#include <map>
#include "../GameObject/GameObject.h"
class GameObjectManager
{
	~GameObjectManager();
	GameObjectManager()=default;
	GameObjectManager(const GameObjectManager& other) = delete;
	const GameObjectManager& operator=(const GameObjectManager& other) = delete;
	std::map<std::string, GameObject*> allObj;

	static GameObjectManager* Instance_;
public:
	static GameObjectManager* Instance()
	{
		if (Instance_ == nullptr)
			Instance_ = new GameObjectManager;
		return Instance_;
	}
	std::map<std::string, GameObject*> AllObj();

	void AddObj(GameObject* obj);
	void RemoveObj(GameObject* obj);

	void Clear();
	GameObject* GetObj(std::string id);
	GameObject* GetLastObj();

};