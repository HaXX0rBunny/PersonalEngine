#include "GOManager.h"
GOManager* GOManager::Instance_=nullptr;
GOManager::~GOManager()
{
	Clear();
	Instance_ = nullptr;
}

std::list<GameObject*> GOManager::AllObj()
{
	return allObj;
}

void GOManager::AddObj(GameObject* obj)
{
	if(obj)
		allObj.push_back(obj);
}

void GOManager::RemoveObj(GameObject* obj)
{
	allObj.remove(obj);
	delete obj;
}
void GOManager::Clear()
{
	for (auto obj : allObj)
	{
		delete obj;
	}
	allObj.clear();
}

GameObject* GOManager::GetLastObj()
{
	if (allObj.empty())
	{
		return nullptr;
	}
	return allObj.back();
}
