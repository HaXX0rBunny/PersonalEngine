#include "TestLevel.h"
#include "../GameObject/GameObject.h"
#include "../Component/SpriteComponent.h"
void Level::TestLevel::Init()
{
	testObj = new GameObject();
	testObj->AddComponent<SpriteComp>();
	SpriteComp* testComp = testObj->GetComponent<SpriteComp>();
	testComp->SetTexture("../Assets/awesomeface.png");
}

void Level::TestLevel::Update()
{
}

void Level::TestLevel::Exit()
{
}
