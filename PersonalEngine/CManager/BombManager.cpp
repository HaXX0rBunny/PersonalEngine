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
//    PendingContainer.push_back(bomb);  // ���� ��⿭�� �߰�
//}
//
//void BombManager::Update()
//{
//    // ���� ��ź ������Ʈ
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
//    // ���� ������� ��ź�� ó��
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
