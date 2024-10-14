#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::Instance_=nullptr;
GameObjectManager::~GameObjectManager()
{
	Clear();
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
	auto it = allObj.find(obj);
	if (it != allObj.end()) {
		delete it->first;  // 메모리 해제
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
		delete it->first;  // 모든 객체 삭제
	}
	allObj.clear();
	
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
    if (allObj.empty()) {
        return nullptr;
    }

    // allObj 맵의 마지막 요소를 가져옴
    const auto& it = std::prev(allObj.end());
    return it->first;  // 첫 번째 요소인 GameObject를 반환
}
