#include "PlayerComponent.h"

PlayerComp::PlayerComp(GameObject* owner) : LogicComponent(owner), moveSpeed(10), spin(1), worldLimit(2000), playMode(false)
{

}

PlayerComp::~PlayerComp()
{

}

void PlayerComp::PlaceBomb()
{
	static int bombCounter = 0;
	std::string bombName = "Bomb_" + std::to_string(bombCounter++);
	GameObject* bomb = new GameObject(bombName);

	bomb->AddComponent<TransformComp>();
	bomb->AddComponent<BombComp>();
	bomb->AddComponent<CollisionComp>();
	// 폭탄의 위치를 플레이어 위치로 설정
	TransformComp* t = own->GetComponent<TransformComp>();
	if (t)
	{
		TransformComp* bombTransform = bomb->GetComponent<TransformComp>();
		bombTransform->SetPos(t->GetPos().x, t->GetPos().y, 5);  // 플레이어와 동일한 위치에 폭탄 생성
		bombTransform->SetScale(100, 100);
	}

	bomb->AddComponent<SpriteComp>();
	SpriteComp* bombSprite = bomb->GetComponent<SpriteComp>();
	bombSprite->SetTexture("Assets/Bomb.png");
	Keystate::keystateSpace = GL_FALSE;

}

void PlayerComp::Update()
{
	DEBUG_PROFILER_START("player");
	if (EngineState::engineState_ == Editor)
		return;
	//if (isColliding)
	//	return;

	TransformComp* t = own->GetComponent<TransformComp>();
	RigidbodyComp* r = own->GetComponent<RigidbodyComp>();
	if (!t || !r)
		return;
	if (t->GetPos().y<worldLimit && t->GetPos().y >-worldLimit)
	{
		if (Keystate::keystateW == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y + moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, 1, 0));
		}
		if (Keystate::keystateS == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y - moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, -1, 0));
		}
		if (Keystate::keystateA == GL_TRUE) {
			t->SetPos(t->GetPos().x - moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(-1, 0, 0));
		}
		if (Keystate::keystateD == GL_TRUE) {
			t->SetPos(t->GetPos().x + moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(1, 0, 0));
		}

		if (t->GetPos().y >= worldLimit)
			t->SetPos(t->GetPos().x, worldLimit - 1);
		else if (t->GetPos().y <= -worldLimit)
			t->SetPos(t->GetPos().x, -worldLimit + 1);
	}
	if (Keystate::keystateSpace == GL_TRUE) {
		PlaceBomb();
	}
	DEBUG_PROFILER_END;
}

void PlayerComp::SetCollisionState(bool state) { isColliding = state; }
void PlayerComp::SetMode(const bool& cb_in) { playMode = cb_in; }
bool PlayerComp::GetMode() { return playMode; }




void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("CompData");

	if (compData != data.end())
	{
		auto ms = compData->find("moveSpeed");
		moveSpeed = ms->begin().value();

		auto s = compData->find("spin");
		spin = s->begin().value();

		auto wl = compData->find("worldLimit");
		worldLimit = wl->begin().value();

		auto pm = compData->find("playMode");
		playMode = pm->begin().value();

	}
}

json PlayerComp::SaveToJson()
{
	json data;
	data["Type"] = GetType();
	json compData;
	compData["moveSpeed"] = moveSpeed;
	compData["spin"] = spin;
	compData["worldLimit"] = worldLimit;
	compData["playMode"] = playMode;
	data["CompData"] = compData;
	return data;
}

BaseRTTI* PlayerComp::CreatePlayerComp()
{
	GameObject* lastObj = GameObjectManager::Instance()->GetLastObj();
	if (lastObj == nullptr) {

		return nullptr;  // 혹은 적절한 예외 처리
	}

	BaseRTTI* out = new PlayerComp(lastObj);

	return out;
}
