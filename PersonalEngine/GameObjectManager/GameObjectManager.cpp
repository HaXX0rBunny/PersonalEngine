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
		delete it->second;  // �޸� ����
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
		delete it->second;  // ��� ��ü ����
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
    return it->second;  // ù ��° ����� GameObject�� ��ȯ
}
