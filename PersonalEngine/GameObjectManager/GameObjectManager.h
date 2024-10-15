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
	std::map<std::string,GameObject*> allObj;

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
	std::map<std::string, GameObject*>  AllObj();
	void RenameKey(const std::string& , const std::string& );
	void AddObj(const std::string& id,GameObject* obj);
	void RemoveObj(const std::string& id);
	void DestroyThis();
	void Clear();
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObj();

};