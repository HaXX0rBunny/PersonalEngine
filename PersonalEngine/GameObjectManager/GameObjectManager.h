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
	std::map<GameObject*, std::string> allObj;

	static GameObjectManager* Instance_;
public:
	static GameObjectManager* Instance()
	{
		if (Instance_ == nullptr)
		{
			Instance_ = new GameObjectManager;
			std::cout << "GameObjMgr 20: Created GameObjectManager" << Instance_ << std::endl;
		}
		return Instance_;
	}
	std::map<GameObject*, std::string>  AllObj();

	void AddObj(GameObject* obj, std::string id = "-1");

	void RemoveObj(GameObject* obj);
	void DestroyThis();
	void Clear();
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObj();

};