#include "TestLevel.h"
#include "../GameObject/GameObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PlayerComponent.h"
#include "../Component/RigidbodyComponent.h"
#include "../Serializer/Serializer.h"

void Level::TestLevel::Init()
{
	//Serializer::Instance()->LoadLevel("test.json");
	//Serializer::Instance()->LoadLevel("test.json");
	//Serializer::Instance()->LoadLevel("test.json");
	//testObj2 = new GameObject("test1");
	//testObj2->AddComponent<SpriteComp>();
	//testObj2->AddComponent<TransformComp>();
	//TransformComp* test2Trans = testObj2->GetComponent<TransformComp>();
	//test2Trans->SetPos(-500, 0);
	//test2Trans->SetScale(500,500);
	//SpriteComp* test2Comp = testObj2->GetComponent<SpriteComp>();
	//test2Comp->SetTexture("Assets/awesomeface.png");



	//testObj = new GameObject("player");
	//testObj->AddComponent<SpriteComp>();
	//testObj->AddComponent<TransformComp>();
	//testObj->AddComponent<PlayerComp>();
	//testObj->AddComponent<RigidbodyComp>();
	//TransformComp* testTrans = testObj->GetComponent<TransformComp>();
	//testTrans->SetPos(500,100);
	//testTrans->SetScale(500, 500);
	//testTrans->SetRot(45);
	//SpriteComp* testComp = testObj->GetComponent<SpriteComp>();
	//testComp->SetTexture();
	//testComp->SetColor(1, 1, 1);
	//testComp->SetAlpha(0.5f);



	//Serializer::Instance()->SaveLevel("Data.json");
}

void Level::TestLevel::Update()
{
}

void Level::TestLevel::Exit()
{
}
