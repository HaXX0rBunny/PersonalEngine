#pragma once
#include "gl.h"
#include "glfw3.h"
#include "GraphicsComponent.h"
#include "../Utility/MyTexture.h"
#include "../Shader.h"
#include <vector>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
class SpriteComp : public GraphicsComponent
{

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
	Shader* vShader;
	Shader* fShader;
	Texture* mtex;
	bool isMeshSet;
	bool isTextureSet;
	//Render mode?
	//Blend mode?
	//Transparency

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
	float GetAlpha();
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