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
	testTrans->SetPos({1, 0, 0});
	testTrans->SetScale({1,1,0});
	SpriteComp* testComp = testObj->GetComponent<SpriteComp>();
	testComp->SetTexture("Assets/awesomeface.png");


	testObj2 = new GameObject();
	testObj2->AddComponent<SpriteComp>();
	testObj2->AddComponent<TransformComp>();
	TransformComp* test2Trans = testObj2->GetComponent<TransformComp>();
	test2Trans->SetPos({-1, 0, 0});
	test2Trans->SetScale({1,1,0});
	SpriteComp* test2Comp = testObj2->GetComponent<SpriteComp>();
	test2Comp->SetTexture("Assets/awesomeface2.png");
}

void Level::TestLevel::Update()
{
}

void Level::TestLevel::Exit()
{
}
