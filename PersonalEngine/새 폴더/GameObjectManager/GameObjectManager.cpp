#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::Instance_=nullptr;
GameObjectManager::~GameObjectManager()
{
	for (auto it : allObj)
	{
		if (it.first)
			delete it.first;
	}
}

std::map<GameObject* , std::string> GameObjectManager::AllObj()
{
	return allObj;
}

void GameObjectManager::AddObj(GameObject* obj, std::string id)
{

	allObj.insert({ obj, id });
	
}


void GameObjectManager::RemoveObj(GameObject* obj)
{
	for (auto& it : allObj)
	{
		if (it.first == obj)
			delete it.first;
	}

	delete obj;
}
void GameObjectManager::Clear()
{
	for (auto it = allObj.begin(); it != allObj.end(); it++)
	{
		delete it->first;
	}

	allObj.clear();
	if (Instance_)
	{
		delete Instance_;
		Instance_ = nullptr;
	}
}

GameObject* GameObjectManager::GetObj(const std::string& id)
{
	for (const auto& pair : allObj) {
		if (pair.second == id) {
			return pair.first;
		}
	}
	// 일치하는 ID가 없을 경우 nullptr 반환
	return nullptr;
		
	
}

GameObject* GameObjectManager::GetLastObj()
{
	if (allObj.empty())
	{
		return nullptr;
	}
	
	const auto& it =allObj.end()--;
	return it->first;
}
