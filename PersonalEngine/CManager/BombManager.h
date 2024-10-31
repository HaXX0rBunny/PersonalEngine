#pragma once
#include "../Component/BombComponent.h"
#include <vector>
#include "../GameObject/GameObject.h"
class BombManager
{

	std::vector<GameObject*> BombContainer;
	BombManager() = default;
	BombManager(const BombManager& other)=delete;
	const BombManager& operator=(const BombManager& other) = delete;
public:
    static BombManager* GetInstance() {
		static BombManager Instance;
		return &Instance;
	}
	void AddBomb(GameObject* bomb);
	BombComp* GetBomb(const std::string& str) const;
	void RemoveBomb(GameObject* bomb);
	void Update();
	void DestroyInstance();
};