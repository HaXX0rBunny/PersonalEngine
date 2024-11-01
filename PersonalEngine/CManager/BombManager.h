//#pragma once
//#include <list>
//#include "../Component/BombComponent.h"
//#include "ComponentManager.h"
//class BombComp;
//class BombManager
//{
//	std::list<BombComp*> BombContainer;
//	std::list<BombComp*> PendingContainer;
//	BombManager() = default;
//	BombManager(const BombManager& other)=delete;
//	const BombManager& operator=(const BombManager& other) = delete;
//public:
//    static BombManager* GetInstance() {
//		static BombManager Instance;
//		return &Instance;
//	}
//	void AddBomb(BombComp* bomb);
//	void RemoveBomb(BombComp* bomb);
//	void Update();
//	void DestroyInstance();
//};