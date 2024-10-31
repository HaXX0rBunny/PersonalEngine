#pragma once
#include "../Utility/GLHeader.h"

#include "GraphicsComponent.h"
#include "../Utility/MyTexture.h"
#include "../Shader.h"
#include <vector>

#include "../Camera/Camera.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

class SpriteComp : public GraphicsComponent
{
	enum polygon {
		Circle,
		Rect,
		Tri
	};
public:
	GLuint vao, vbo, ebo;

	struct Vertex {
		float position[3]; 
		float color[3];    
		float texCoords[2]; 
	};
private:
	glm::vec3 mColor;
	float Alpha;
	//texture
	//AEGfxTexture* mTex;
	Shader* mShader;

	Texture* mtex;
	bool isMeshSet;
	bool isTextureSet;
	//Render mode?
	//Blend mode?
	//Transparency
	polygon SpriteType;
	std::string textureName;
public:
	
	SpriteComp(GameObject* owner);
	~SpriteComp();
	void Update() override;
	//draw

	//Gettors/Settors
	void SetColor(const float& r, const float& g , const float& b);
	void SetColor(const glm::vec3& other);
	void SetMesh();
	void SetTexture(const std::string& filepath= "./Assets/Default.png");
	void SetAlpha(const float& a);
	void SetPolyType(const polygon& ce_in);
	float GetAlpha();
	const polygon& GetPolyType();
	glm::vec3& Getcolor() { return mColor; };
	const std::string& GetPath() { return textureName; };
	void Render();
	static std::string GetType()
	{
		return "SpriteComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	static BaseRTTI* CreateSpriteComp();
};