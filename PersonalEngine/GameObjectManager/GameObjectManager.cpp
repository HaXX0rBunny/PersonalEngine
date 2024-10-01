#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::Instance_=nullptr;
GameObjectManager::~GameObjectManager()
{
	Clear();
	Instance_ = nullptr;
}

std::map<std::string, GameObject*> GameObjectManager::AllObj()
{
	return allObj;
}

void GameObjectManager::AddObj(GameObject* obj)
{
	if(obj)
		allObj.insert({ "", obj });
}

void GameObjectManager::RemoveObj(GameObject* obj)
{
	for (auto& it : allObj)
	{
		if (it.second == obj)
			delete it.second;
	}

	delete obj;
}
void GameObjectManager::Clear()
{
	for (auto it = allObj.begin(); it != allObj.end(); it++)
	{
		delete it->second;
	}

	allObj.clear();
}

GameObject* GameObjectManager::GetObj(std::string id)
{
	return nullptr;
}

GameObject* GameObjectManager::GetLastObj()
{
	/*if (allObj.empty())
	{
		return nullptr;
	}
	return allObj.back();*/
}
