//#pragma once
//#include "gl.h"
//#include "glfw3.h"
//#include <glm.hpp>
//#include <gtc/type_ptr.hpp>
//
//#include "../Component/TransformComponent.h"
//#include "EngineComponent.h"
//#include "../GameObjectManager/GameObjectManager.h"
//#define  fwidth_Line 5.f // 1.f~ 10.f   this is Limit width 
//
//class CollisionComp : public EngineComponent
//{
//	glm::vec2 vPos;
//	glm::vec2 vScale;
//	float fRot;
//	bool isCollider;
//	bool isVisible;
//	GLuint vao, vbo, ebo;
//public:
//	CollisionComp(GameObject* owner);
//	~CollisionComp();
//
//	struct Vertex {
//		float position[3];
//		float color[3];
//	};
//
//
//	void Update() override;
//	void Render();
//	//Gettors
//	const glm::vec2& GetPos() const { return vPos; };
//	const glm::vec2& GetScale() const { return vScale; };
//	const float& GetRot() const { return fRot; };
//	const bool& GetVisible() const { return isVisible; };
//	//Mutators
//	void SetCollision();
//	void SetCollision(const glm::vec3& vPos_i, const glm::vec3& vScale_i, const float& fRot_i);
//	void SetCollision(const float& fPosx_i, const float& fPosy_i, const float& fScalex_i, const float& fSacaley_i, const float& fRot_i);
//	void SetPos(const float& x, const float& y);
//	void SetPos(const glm::vec3& vPosi);
//	void SetScale(const float& x, const float& y);
//	void SetScale(const glm::vec3& vScalei);
//	void SetRot(const float& fRoti);
//	void SetVisible(const bool& cb_in);
//	void SetCollisionBox();
//	
//
//
//	static std::string GetType()
//	{
//		return "CollisionComp";
//	}
//};