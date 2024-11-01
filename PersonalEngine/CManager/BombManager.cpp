//#include "BombManager.h"
//#include "../GameObjectManager/GameObjectManager.h"
//void BombManager::AddBomb(BombComp* bomb)
//{
//	if (bomb)
//		BombContainer.push_back(bomb);
//}
//
//
//void BombManager::RemoveBomb(BombComp* bomb)
//{
//    if (!bomb) return;
//    PendingContainer.push_back(bomb);  // 제거 대기열에 추가
//}
//
//void BombManager::Update()
//{
//    // 기존 폭탄 업데이트
//    for (auto it = BombContainer.begin(); it != BombContainer.end();)
//    {
//        if (*it && (*it)->GetOwner()) {
//            (*it)->Update();
//            ++it;
//        }
//        else {
//            it = BombContainer.erase(it);
//        }
//    }
//    // 제거 대기중인 폭탄들 처리
//    for (auto bomb : PendingContainer)
//    {
//        if (bomb) {
//            auto it = std::find(BombContainer.begin(), BombContainer.end(), bomb);
//            if (it != BombContainer.end()) {
//                if (bomb->GetOwner()) {
//                    GameObjectManager::Instance()->RemoveObj(bomb->GetOwner()->GetName());
//                }
//                BombContainer.erase(it);
//            }
//        }
//    }
//    PendingContainer.clear();
//}
//
//void BombManager::DestroyInstance()
//{
//    PendingContainer.clear();
//    BombContainer.clear();
//}
