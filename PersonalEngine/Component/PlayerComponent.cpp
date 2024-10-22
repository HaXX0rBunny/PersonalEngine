#include "PlayerComponent.h"

PlayerComp::PlayerComp(GameObject* owner):EngineComponent(owner), moveSpeed(10), spin(1), worldLimit(375), playMode(false)
{

}

PlayerComp::~PlayerComp()
{

}

void PlayerComp::Update()
{
	if (EngineState::engineState_ == Editor)
		return;
	TransformComp* t = own->GetComponent<TransformComp>();
	RigidbodyComp* r = own->GetComponent<RigidbodyComp>();
	if (!t||!r)
		return;
	if (t->GetPos().y<worldLimit && t->GetPos().y >-worldLimit)
	{
		if (Keystate::keystateW == GL_TRUE) {
			t->SetPos( t->GetPos().x, t->GetPos().y + moveSpeed );
		}
		if (Keystate::keystateS == GL_TRUE) {
			t->SetPos( t->GetPos().x, t->GetPos().y - moveSpeed );
		}
		if (Keystate::keystateA == GL_TRUE) {
			t->SetPos(t->GetPos().x - moveSpeed, t->GetPos().y );
		}
		if (Keystate::keystateD == GL_TRUE) {
			t->SetPos(t->GetPos().x + moveSpeed, t->GetPos().y);
		}
		if (Keystate::keystateSpace == GL_TRUE) {
			CreateBomb();
		}
		if (t->GetPos().y >= worldLimit)
			t->SetPos( t->GetPos().x, worldLimit - 1 );
		else if (t->GetPos().y <= -worldLimit)
			t->SetPos( t->GetPos().x, -worldLimit + 1 );
	}
}

void PlayerComp::CreateBomb()
{
	// ���ο� ��ź ������Ʈ ����
	GameObject* bomb = new GameObject("Bomb");
	//bomb->AddComponent<TransformComp>();

	//// ��ź�� ��ġ�� �÷��̾� ��ġ�� ����
	//TransformComp* t = own->GetComponent<TransformComp>();
	//if (t)
	//{
	//	TransformComp* bombTransform = bomb->GetComponent<TransformComp>();
	//	bombTransform->SetPos(t->GetPos().x, t->GetPos().y);  // �÷��̾�� ������ ��ġ�� ��ź ����
	//	bombTransform->SetScale(100, 100);
	//}

	//// �ʿ��� ������Ʈ�� ��ź�� �߰�
	//bomb->AddComponent<RigidbodyComp>();  
	//bomb->AddComponent<SpriteComp>();  
	//SpriteComp * bombSprite=bomb->GetComponent<SpriteComp>();
	//bombSprite->SetTexture("Assets/Bomb.png");
	//// ��ź�� ������ �̸� �ο�
	std::string bombName = "Bomb_" + std::to_string(GameObjectManager::Instance()->AllObj().size());

	// GameObjectManager�� ��ź ������Ʈ �߰�
	GameObjectManager::Instance()->RenameKey("Bomb",bombName);


}

void PlayerComp::SetMode(const bool& cb_in)
{
	playMode = cb_in;
}

bool PlayerComp::GetMode()
{
	return playMode;
}


void PlayerComp::LoadFromJson(const json& data)
{

}

json PlayerComp::SaveToJson()
{
	return json();
}

BaseRTTI* PlayerComp::CreateTransformComp()
{
	return nullptr;
}
