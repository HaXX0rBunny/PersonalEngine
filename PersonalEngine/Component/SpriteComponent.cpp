#include "SpriteComponent.h"
#include "../ResourceManager/ResourceManager.h"
SpriteComp::SpriteComp(GameObject* owner) :GraphicsComponent(owner), Alpha(1.0f), mtex(nullptr)
{
	mColor = {0,0,0};
}

SpriteComp::~SpriteComp()
{
	if (mtex)
	{
		TextureUnload(mtex);
	}
}

void SpriteComp::Update()
{
}

void SpriteComp::SetTexture(const std::string& filepath)
{
	if (textureName != filepath)
	{
		// 기존 텍스처 언로드
		ResourceManager::GetInstance()->UnloadResource(textureName);
	}
	textureName = filepath;

	// 올바른 타입으로 텍스처 가져오기
	mtex = ResourceManager::GetInstance()->GetResource<Texture>(textureName);
}


void SpriteComp::SetAlpha(float a)
{
	Alpha = a;
}

float SpriteComp::GetAlpha()
{
	return 0.0f;
}

void SpriteComp::LoadFromJson(const json& data)
{
}

json SpriteComp::SaveToJson()
{
	return json();
}

BaseRTTI* SpriteComp::CreateSpriteComp()
{
	return nullptr;
}
