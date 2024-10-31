#include "BombComponent.h"
#include "../GameObject/GameObject.h"
BombComp::BombComp(GameObject* owner) : BaseComponent(owner)
{

}
BombComp::~BombComp()
{

}
void BombComp::Update()
{
	if (Keystate::keystateSpace == GL_TRUE) {
		CreateBomb();
	}
}

void BombComp::CreateBomb()
{
	GameObject* bomb = new GameObject("Bomb");
	BombManager::GetInstance()->AddBomb(own);
	bomb->AddComponent<TransformComp>();

	// 폭탄의 위치를 플레이어 위치로 설정
	TransformComp* t = own->GetComponent<TransformComp>();
	if (t)
	{
		TransformComp* bombTransform = bomb->GetComponent<TransformComp>();
		bombTransform->SetPos(t->GetPos().x, t->GetPos().y, 5);  // 플레이어와 동일한 위치에 폭탄 생성
		bombTransform->SetScale(100, 100);
	}

	// 필요한 컴포넌트를 폭탄에 추가
	bomb->AddComponent<RigidbodyComp>();
	bomb->AddComponent<SpriteComp>();
	SpriteComp* bombSprite = bomb->GetComponent<SpriteComp>();
	bombSprite->SetTexture("Assets/Bomb.png");
	// 폭탄에 고유한 이름 부여
	std::string bombName = "Bomb_" + std::to_string(GameObjectManager::Instance()->AllObj().size());

	// GameObjectManager에 폭탄 오브젝트 추가
	GameObjectManager::Instance()->RenameKey("Bomb", bombName);
	Keystate::keystateSpace = GL_FALSE;
}



void BombComp::Explosion()
{
}

void BombComp::BombEffect()
{
}
void BombComp::LoadFromJson(const json& data)
{
}
json BombComp::SaveToJson()
{
	return json();
}

BaseRTTI* BombComp::CreateBomnComp()
{
	return nullptr;
}
