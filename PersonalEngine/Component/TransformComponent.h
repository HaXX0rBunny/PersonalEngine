#pragma once
#include "EngineComponent.h"
#include "../Utility/Matrix.h"
#include "../Utility/Profiler.h"
class TransformComp : public EngineComponent
{
	glm::vec3 pos;
    glm::vec3 scale;	
	float rot;

	glm::mat4 trancsformMatrix;
	glm::vec3 prePos;
	void CalculateMatrix();
public:
	TransformComp& operator=(const TransformComp& other);
	TransformComp(GameObject* owner);

	~TransformComp();
	void Update() override;
	//Gettors
	const glm::vec3& GetPos() const { return pos; };
	const glm::vec3& GetScale() const { return scale; };
	const float& GetRot() const { return rot; };
	const glm::mat4& GetMatrix()const;
	//Mutators
	const glm::vec3& GetPrePos() const { return prePos; };
	void SetPos(const float& x, const float& y, const float& z = 0);
	void SetScale(const float& x, const float& y, const float& z = 1);
	void SetPos(const glm::vec3& otherPos);
	void SetScale(const glm::vec3& otherScale);
	void SetRot(const float& otherRot);
	void PrintMatrix();
	glm::vec3 GetPreviousPosition() const;
	static std::string GetType()
	{
		return "TransformComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateTransformComp();
};
