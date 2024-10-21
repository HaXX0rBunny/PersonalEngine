#include "RigidbodyComponent.h"

bool RigidbodyComp::CheckEpsilon(float v, float Ep)
{
	if (v< -Ep || v > Ep)
		return true;
	return false;
}


RigidbodyComp::RigidbodyComp(GameObject* owner): EngineComponent(owner)
{
	Velocity.x = 0;
	Velocity.y = 0;
	MaxVelocity.x = 100;
	MaxVelocity.y = 100;
}

void RigidbodyComp::AddVelocity(float x, float y)
{
	Velocity.x += x;
	Velocity.y += y;
	Velocity.x = std::clamp(Velocity.x, -MaxVelocity.x, MaxVelocity.x);

	Velocity.y = std::clamp(Velocity.y, -MaxVelocity.y, MaxVelocity.y);
}

glm::vec2 RigidbodyComp::GetVelocity()
{
    return Velocity;
}

void RigidbodyComp::SetVelocity(float x, float y)
{
	Velocity.x = x;
	Velocity.y = y;
}

void RigidbodyComp::ClearVelocity()
{
	Velocity.x = 0;
	Velocity.y = 0;



}

void RigidbodyComp::Clamp(const float& cf_velocity, const float& cf_min, const float& cf_max)
{


}


void RigidbodyComp::Update()
{
	TransformComp* t = own->GetComponent<TransformComp>();
	if (!t)
		return;
	float x = t->GetPos().x + static_cast<float>(Velocity.x * Time::delta_time);
	float y = t->GetPos().y + static_cast<float>(Velocity.y * Time::delta_time);

	Velocity.x /= drag;

	Velocity.y /= drag;

	if (CheckEpsilon(Velocity.x) == false)
		Velocity.x = 0;

	if (CheckEpsilon(Velocity.y) == false)
		Velocity.y = 0;

	t->SetPos( x,y );
}

void RigidbodyComp::LoadFromJson(const json& data)
{
}

json RigidbodyComp::SaveToJson()
{
    return json();
}

BaseRTTI* RigidbodyComp::CreateRigidbodyComp()
{
    return nullptr;
}
