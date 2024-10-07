#pragma once
#include "gl.h"
#include "glfw3.h"
#include "GraphicsComponent.h"
#include "../Utility/MyTexture.h"
#include <vector>

#include <string>
class SpriteComp : public GraphicsComponent
{

	//mesh of points (quad)
	//All mye bjects have the same quad;
	// so i will not make it a member variable
	//text coords uv // Maybe later
	//color
public:
	GLuint vao, vbo, ebo;
	struct Color
	{
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
	};
	struct Vertex {
		float position[3]; // 위치 (x, y, z)
		float color[3];    // 컬러 (r, g, b)
		float texCoords[2]; // 텍스처 좌표 (u, v)
	};
private:
	Color mColor;
	float Alpha;
	//texture
	//AEGfxTexture* mTex;
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
	Color& Getcolor() { return mColor; };
	void SetTexture(const std::string& filepath);
	void SetAlpha(float a);
	float GetAlpha();
	void SetMesh();
	void Render();
	static std::string GetType()
	{
		return "SpriteComp";
	}
	void LoadFromJson(const json& data)override;

	json SaveToJson()override;
	static BaseRTTI* CreateSpriteComp();
};