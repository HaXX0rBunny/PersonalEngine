#include "PlayerComponent.h"

PlayerComp::PlayerComp(GameObject* owner) : LogicComponent(owner), spin(1), worldLimit(2000), playMode(false), Player(Player1)
{

	state.BombPower=1;
	state.moveSpeed = 10;
	state.BombCount = 1;
	state.isGrab = false;
	state.isImune = false;
	state.isKick = false;
	flagDirection = 1;
}

PlayerComp::~PlayerComp()
{

}

void PlayerComp::PlaceBomb()
{
	static int bombCounter = 0;
	std::string bombName = "Bomb_" + std::to_string(bombCounter++);
	GameObject* bomb = new GameObject(bombName);
	bomb->ObjectTag = GameObject::Tag::Bomb;
	bomb->AddComponent<TransformComp>();
	bomb->AddComponent<BombComp>();

	
	bomb->AddComponent<CollisionComp>();
	// 폭탄의 위치를 플레이어 위치로 설정
	TransformComp* t = own->GetComponent<TransformComp>();
	if (t)
	{
		TransformComp* bombTransform = bomb->GetComponent<TransformComp>();
		bombTransform->SetPos(t->GetPos().x, t->GetPos().y, 5);  // 플레이어와 동일한 위치에 폭탄 생성
		bombTransform->SetScale(32, 32);
	}


	auto setBomb= bomb->GetComponent<BombComp>();
	setBomb->SetPower(state.BombPower);
	bomb->AddComponent<SpriteComp>();
	SpriteComp* bombSprite = bomb->GetComponent<SpriteComp>();
	bombSprite->SetTexture("Assets/Bomb.png");


}

void PlayerComp::Update()
{
	DEBUG_PROFILER_START("player");
	if (EngineState::engineState_ == Editor)
		return;
	//if (isColliding)
	//	return;
	if(Player==Player1)
		Player_1_Keymap();
	else if (Player == Player2)
		Player_2_Keymap();
	
	DEBUG_PROFILER_END;
}
void PlayerComp::Player_1_Keymap()
{
	TransformComp* t = own->GetComponent<TransformComp>();
	RigidbodyComp* r = own->GetComponent<RigidbodyComp>();
	if (!t || !r)
		return;
	if (t->GetPos().y<worldLimit && t->GetPos().y >-worldLimit)
	{
		if (Keystate::keystateW == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y + state.moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, 1, 0));
			flagDirection = 3;
		}
		if (Keystate::keystateS == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y - state.moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, -1, 0));
			flagDirection = 1;
		}
		if (Keystate::keystateA == GL_TRUE) {
			t->SetPos(t->GetPos().x - state.moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(-1, 0, 0));
			flagDirection = 2;
		}
		if (Keystate::keystateD == GL_TRUE) {
			t->SetPos(t->GetPos().x + state.moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(1, 0, 0));
			flagDirection = 4;
		}

		if (t->GetPos().y >= worldLimit)
			t->SetPos(t->GetPos().x, worldLimit - 1);
		else if (t->GetPos().y <= -worldLimit)
			t->SetPos(t->GetPos().x, -worldLimit + 1);
	}
	if (Keystate::keystateSpace == GL_TRUE) {
		PlaceBomb();
		Keystate::keystateSpace = GL_FALSE;
	}
}
void PlayerComp::Player_2_Keymap()
{
	TransformComp* t = own->GetComponent<TransformComp>();
	RigidbodyComp* r = own->GetComponent<RigidbodyComp>();
	if (!t || !r)
		return;
	if (t->GetPos().y<worldLimit && t->GetPos().y >-worldLimit)
	{
		if (Keystate::keystateUp == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y + state.moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, 1, 0));
			flagDirection = 3;
		}
		if (Keystate::keystateDown == GL_TRUE) {
			t->SetPos(t->GetPos().x, t->GetPos().y - state.moveSpeed);
			Camera::GetInstance()->MoveCamera(glm::vec3(0, -1, 0));
			flagDirection = 1;
		}
		if (Keystate::keystateLeft == GL_TRUE) {
			t->SetPos(t->GetPos().x - state.moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(-1, 0, 0));
			flagDirection = 2;
		}
		if (Keystate::keystateRight == GL_TRUE) {
			t->SetPos(t->GetPos().x + state.moveSpeed, t->GetPos().y);
			Camera::GetInstance()->MoveCamera(glm::vec3(1, 0, 0));
			flagDirection = 4;
		}

		if (t->GetPos().y >= worldLimit)
			t->SetPos(t->GetPos().x, worldLimit - 1);
		else if (t->GetPos().y <= -worldLimit)
			t->SetPos(t->GetPos().x, -worldLimit + 1);
	}
	if (Keystate::keystateRShift == GL_TRUE) {
		PlaceBomb();
		Keystate::keystateRShift = GL_FALSE;
	}
}

const int& PlayerComp::GetDirection()
{
	return flagDirection;
}

void PlayerComp::SetCollisionState(bool state) { isColliding = state; }
void PlayerComp::SetMode(const bool& cb_in) { playMode = cb_in; }
void PlayerComp::SetPlayer(const PlayerNumber& ce_in){	Player = ce_in;}


bool PlayerComp::GetMode() { return playMode; }

void PlayerComp::SetState(const ItemList& ce_in)
{
	switch (ce_in)
	{
	case SpeedUp:
		state.moveSpeed += 2;
		break;
	case PowerUp:
		state.BombPower++;
		break;
	case GrabUp:
		state.isGrab = true;
		break;
	case BombUp:
		state.BombCount++;
		break;
	case Imune:
		state.isImune = true;
		break;
	case RemoteUp:
		state.isRemote = true;
		break;
	case Curse:
		state.isCurse = true;
		break;
	case KickUp:
		state.isKick = true;
		break;
	default:
		break;
	}
}




void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("CompData");

	if (compData != data.end())
	{
		auto ms = compData->find("moveSpeed");
		state.moveSpeed = ms->begin().value();

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
	compData["moveSpeed"] = state.moveSpeed;
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
