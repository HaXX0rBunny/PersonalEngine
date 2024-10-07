#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::Instance_=nullptr;
GameObjectManager::~GameObjectManager()
{
	
}

std::map<std::string, GameObject*> GameObjectManager::AllObj()
{
	return allObj;
}

void GameObjectManager::AddObj(GameObject* obj, std::string id)
{
	allObj.insert({ id, obj });
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
	if (Instance_)
	{
		delete Instance_;
		Instance_ = nullptr;
	}
}

GameObject* GameObjectManager::GetObj(std::string id)
{
	if (allObj.empty())
		return nullptr;
	return allObj.find(id)->second;
		
	
}

GameObject* GameObjectManager::GetLastObj()
{
	if (allObj.empty())
	{
		return nullptr;
	}
	
	const auto& it =allObj.end()--;
	return it->second;
}
