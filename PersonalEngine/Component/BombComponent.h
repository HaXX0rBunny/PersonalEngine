#pragma once
#include "SpriteComponent.h"
#include "../Utility/InputProcess.h"
#include "../Utility/Time.h"
#include "LogicComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "../Utility/Time.h"

enum BombType {
	Default,
	Timebomb,
	Dynamite,
	Boobytrap,
	melloondago,
};
class ExplosionEffectComponent : public LogicComponent {
private:
	float duration;
	float currentTime;

public:
	ExplosionEffectComponent(GameObject* owner) : LogicComponent(owner), duration(0.5f), currentTime(0.0f) {}

	void SetDuration(float time) { duration = time; }

	void Update() override {
		currentTime += Time::delta_time;
		if (currentTime >= duration) {
			GameObjectManager::Instance()->RemoveObj(GetOwner()->GetName());
		}
	}
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;
	static BaseRTTI* CreateBombComp();
	static std::string GetType()
	{
		return "ExplosionEffectComponent";
	}
};
class BombComp : public LogicComponent
{
	double startTime;  // 생성 시점 저장
	static int BombCount;
	float LifeTime;
	bool isExploded;
	int BombPower;
	BombType Bombtype;

public:
	BombComp(GameObject* owner);
	~BombComp();
	void Update() override;
	void Explode();
	bool HandleCollisions(const std::vector<GameObject*>& colliders);
	std::vector<GameObject*> CheckCollisionAtPosition(const glm::vec2& pos);

	// 불필요한 빈 함수들 제거
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;
	static BaseRTTI* CreateBombComp();
	static std::string GetType()
	{
		return "BombComp";
	}
private:
	void ProcessExplosion();
	void CreateExplosionEffect(const glm::vec2& position);
	glm::vec2 CalculateExplosionPosition(const glm::vec2& direction, int distance);
};
