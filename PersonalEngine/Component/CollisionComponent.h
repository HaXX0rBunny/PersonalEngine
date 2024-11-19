#pragma once
#include "../Component/SpriteComponent.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "ItemComponent.h"
#include "../Component/TransformComponent.h"
#include "EngineComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/Entity.h"
#include "../Shader.h"
#define  fwidth_Line 100.f // 1.f~ 10.f   this is Limit width 
class CollisionComp : public EngineComponent , public Entity
{
	bool isCollider;
	bool isVisible;
	GLuint vao, vbo, ebo;
	glm::mat4 transformMatrix;
	Shader* mShader;
public:
	struct Vertex {
		float position[3];
		float color[3];
		float Line;
	};

public:
	CollisionComp(GameObject* owner);
	~CollisionComp();

	void Update() override;
	void OnEvent(Event* event) override;

	std::vector<glm::vec3> CalculateAxes(const glm::mat4& playerMatrix, const glm::mat4& otherMatrix) const;
	void Render();

	bool CheckCollision(const CollisionComp* other) const;
	void ProjectOntoAxis(const glm::vec3& pos, const glm::vec3& scale, float rot, const glm::vec3& axis, float& min, float& max) const;
	bool DetectCollision(const glm::mat4& matrix1, const glm::mat4& matrix2, const std::vector<glm::vec3>& axes, glm::vec3& smallestAxis, float& minOverlap) const;
	void ProjectOntoAxis(const glm::mat4& transform, const glm::vec3& axis, float& min, float& max) const;

	void SetVisible(const bool& cb_in);
	void SetCollisionBox();

	static std::string GetType()
	{
		return "CollisionComp";
	}

	void LoadFromJson(const json& data);

	json SaveToJson()override;
	//For the RTTI
	static BaseRTTI* CreateCollisionComp();
private:
	glm::mat4 CreateTransformMatrix(const TransformComp* transform) const;
};

