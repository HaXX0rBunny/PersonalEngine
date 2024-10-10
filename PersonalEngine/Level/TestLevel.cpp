#include "TestLevel.h"
#include "../GameObject/GameObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/TransformComponent.h"


void Level::TestLevel::Init()
{
	testObj = new GameObject();
	testObj->AddComponent<SpriteComp>();
	testObj->AddComponent<TransformComp>();
	TransformComp* testTrans = testObj->GetComponent<TransformComp>();
	testTrans->SetPos({0, 0, 0});
	testTrans->SetScale({1,1,0});
	SpriteComp* testComp = testObj->GetComponent<SpriteComp>();
	testComp->SetTexture("Assets/awesomeface.png");
}

void Level::TestLevel::Update()
{
}

void Level::TestLevel::Exit()
{
}
