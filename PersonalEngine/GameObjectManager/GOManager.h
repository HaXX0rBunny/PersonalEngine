#pragma once
#include <list>
#include "../GameObject/GameObject.h"
class GOManager
{
	~GOManager();
	GOManager()=default;
	GOManager(const GOManager& other) = delete;
	const GOManager& operator=(const GOManager& other) = delete;
	std::list<GameObject*> allObj;
	static GOManager* Instance_;
public:
	static GOManager* Instance()
	{
		if (Instance_ == nullptr)
			Instance_ = new GOManager;
		return Instance_;
	}
	std::list<GameObject*> AllObj();
	void AddObj(GameObject* obj);
	void RemoveObj(GameObject* obj);
	void Clear();
	GameObject* GetLastObj();

};