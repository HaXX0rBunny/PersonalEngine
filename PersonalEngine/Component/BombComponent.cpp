#include "BombComponent.h"
#include "../GameObject/GameObject.h"
void BomnComp::Update()
{
	if (Keystate::keystateSpace == GL_TRUE) {
		CreateBomb();
	}
}

void BomnComp::CreateBomb()
{
	GameObject* bomb = new GameObject("Bomb");
	bomb->AddComponent<TransformComp>();

	// ��ź�� ��ġ�� �÷��̾� ��ġ�� ����
	TransformComp* t = own->GetComponent<TransformComp>();
	if (t)
	{
		TransformComp* bombTransform = bomb->GetComponent<TransformComp>();
		bombTransform->SetPos(t->GetPos().x, t->GetPos().y, 5);  // �÷��̾�� ������ ��ġ�� ��ź ����
		bombTransform->SetScale(100, 100);
	}

	// �ʿ��� ������Ʈ�� ��ź�� �߰�
	bomb->AddComponent<RigidbodyComp>();
	bomb->AddComponent<SpriteComp>();
	SpriteComp* bombSprite = bomb->GetComponent<SpriteComp>();
	bombSprite->SetTexture("Assets/Bomb.png");
	// ��ź�� ������ �̸� �ο�
	std::string bombName = "Bomb_" + std::to_string(GameObjectManager::Instance()->AllObj().size());

	// GameObjectManager�� ��ź ������Ʈ �߰�
	GameObjectManager::Instance()->RenameKey("Bomb", bombName);

}

void BomnComp::LoadFromJson(const json& data)
{
}

json BomnComp::SaveToJson()
{
	return json();
}

BaseRTTI* BomnComp::CreateBomnComp()
{
	return nullptr;
}
