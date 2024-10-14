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
		delete it->first;  // �޸� ����
		allObj.erase(it);  // �ʿ��� ����
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
		delete it->first;  // ��� ��ü ����
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
	// ��ġ�ϴ� ID�� ���� ��� nullptr ��ȯ
	return nullptr;
		
	
}

GameObject* GameObjectManager::GetLastObj()
{
    if (allObj.empty()) {
        return nullptr;
    }

    // allObj ���� ������ ��Ҹ� ������
    const auto& it = std::prev(allObj.end());
    return it->first;  // ù ��° ����� GameObject�� ��ȯ
}
