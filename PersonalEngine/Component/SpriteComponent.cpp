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
		// ���� �ؽ�ó ��ε�
		ResourceManager::GetInstance()->UnloadResource(textureName);
	}
	textureName = filepath;

	// �ùٸ� Ÿ������ �ؽ�ó ��������
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
