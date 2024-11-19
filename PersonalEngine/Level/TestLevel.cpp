#include "TestLevel.h"
#include "../GameObject/GameObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PlayerComponent.h"
#include "../Component/RigidbodyComponent.h"
#include "../Serializer/Serializer.h"
#include "../Component/CollisionComponent.h"
#include "../Component/BombComponent.h"
void Level::TestLevel::Init()
{
	//Serializer::Instance()->LoadLevel("test.json");
	//Serializer::Instance()->LoadLevel("test.json");
	//Serializer::Instance()->LoadLevel("test.json");
	testObj2 = new GameObject("test1");
	testObj2->ObjectTag = GameObject::Tag::Wall;
	testObj2->AddComponent<SpriteComp>();
	testObj2->AddComponent<TransformComp>();
	testObj2->AddComponent<RigidbodyComp>();
	testObj2->AddComponent<CollisionComp>();
	TransformComp* test2Trans = testObj2->GetComponent<TransformComp>();
	test2Trans->SetPos(0, 0, 2);
	test2Trans->SetScale(40,40);
	SpriteComp* test2Comp = testObj2->GetComponent<SpriteComp>();
	test2Comp->SetTexture("Assets/awesomeface.png");


	testObj3 = new GameObject("test2");

	testObj3->AddComponent<SpriteComp>();
	testObj3->AddComponent<TransformComp>();
	testObj3->AddComponent<RigidbodyComp>();
	testObj3->AddComponent<CollisionComp>();
	testObj3->AddComponent<BlockComp>();
	TransformComp* test3Trans = testObj3->GetComponent<TransformComp>();
	test3Trans->SetPos(40, 40, 2);
	test3Trans->SetScale(40, 40);
	SpriteComp* test3Comp = testObj3->GetComponent<SpriteComp>();
	test3Comp->SetTexture("Assets/awesomeface2.png");
	test3Comp->SetColor(150, 1, 1);



	testObj = new GameObject("player");
	testObj->ObjectTag = GameObject::Tag::Player;
	testObj->AddComponent<SpriteComp>();
	testObj->AddComponent<TransformComp>();

	testObj->AddComponent<PlayerComp>();
	testObj->AddComponent<RigidbodyComp>();
	testObj->AddComponent<CollisionComp>();

	TransformComp* testTrans = testObj->GetComponent<TransformComp>();
	testTrans->SetPos(600,0,-0);
	testTrans->SetScale(40, 40);

	SpriteComp* testComp = testObj->GetComponent<SpriteComp>();
	testComp->SetTexture();


	Serializer::Instance()->SaveLevel("Data.json");
}

void Level::TestLevel::Update()
{
}

void Level::TestLevel::Exit()
{
}
