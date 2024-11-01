#include "BombComponent.h"
#include "../GameObject/GameObject.h"
#include "../CManager/ComponentManager.h"
BombComp::BombComp(GameObject* owner):LogicComponent(owner)
{
	startTime = glfwGetTime();
	BombCount=0;
	LifeTime = 3.0f;
	isExploded = false;
	BombPower=1;
	Bombtype=Default;
}

BombComp::~BombComp()
{

}
void BombComp::Update()
{
	//if (isExploded) return;

	double currentElapsedTime = glfwGetTime() - startTime;
	if (currentElapsedTime >= LifeTime) {
		Explode();
	}
	
}
void BombComp::Explode() {
	//if (isExploded) return;
	isExploded = true;
	GameObjectManager::Instance()->RemoveObj(own->GetName());
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
