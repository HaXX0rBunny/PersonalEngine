#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::Instance_=nullptr;
GameObjectManager::~GameObjectManager()
{
	Clear();
}

std::map<std::string, GameObject*> GameObjectManager::AllObj()
{
	return allObj;
}

void GameObjectManager::AddObj(const std::string& id,GameObject* obj)
{
	const auto& it = allObj.find(id);
	if(it == allObj.end())
		allObj.insert({ id, obj });
	
}


void GameObjectManager::RemoveObj(const std::string& id)
{
	auto it = allObj.find(id);
	if (it != allObj.end()) {
		delete it->second;  // 메모리 해제
		allObj.erase(it);  // 맵에서 제거
	}
}
void GameObjectManager::DestroyThis()
{
	if (Instance_)
	{
		delete Instance_;
		Instance_ = nullptr;
	}
}
void GameObjectManager::Clear()
{
	for (auto it = allObj.begin(); it != allObj.end(); it++)
	{
		delete it->second;  // 모든 객체 삭제
	}
	allObj.clear();
	
}

GameObject* GameObjectManager::GetObj(const std::string& id)
{
	for (const auto& pair : allObj) {
		if (pair.first == id) {
			return pair.second;
		}
	}
	// 일치하는 ID가 없을 경우 nullptr 반환
	return nullptr;
		
	
}

GameObject* GameObjectManager::GetLastObj()
{
    if (allObj.empty()) {
        return nullptr;
    }

    // allObj 맵의 마지막 요소를 가져옴
    const auto& it = std::prev(allObj.end());
    return it->second;  // 첫 번째 요소인 GameObject를 반환
}
