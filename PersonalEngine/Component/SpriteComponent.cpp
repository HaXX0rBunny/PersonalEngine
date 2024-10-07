#include "SpriteComponent.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Utility/MyTexture.h"
SpriteComp::SpriteComp(GameObject* owner) :GraphicsComponent(owner), Alpha(1.0f), mtex(nullptr), isMeshSet(false), isTextureSet(false)
{
	vao = 0, vbo = 0, ebo = 0;
	mColor = {0,0,0};
	SetMesh();
}

SpriteComp::~SpriteComp()
{
	if (mtex)
	{
		TextureUnload(mtex);
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void SpriteComp::Update()
{
	
	if (isMeshSet&& isTextureSet) 
		Render();
	
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
	if (mtex != nullptr) {
		isTextureSet = true; // �ؽ�ó�� ���������� �ε�Ǿ����� ǥ��
	}
}


void SpriteComp::SetAlpha(float a)
{
	Alpha = a;
}

float SpriteComp::GetAlpha()
{
	return Alpha;
}

void SpriteComp::SetMesh()
{

	std::vector<Vertex> vertices = {
		// ���� ��� ����
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� �ϴ� ����
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� �ϴ� ����
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� ��� ����
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}  // ��ġ, �÷�, �ؽ�ó ��ǥ
	};

	// �ε��� �迭�� std::vector�� �������� ������, ���� �迭�� ���
	unsigned int indices[] = {
		0, 1, 3, // ù ��° �ﰢ��
		1, 2, 3  // �� ��° �ﰢ��
	};
	// VAO, VBO, EBO ����
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// VAO ���ε� (������ ����)
	glBindVertexArray(vao);

	// VBO ���ε� �� ������ ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// EBO ���ε� �� ������ ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���� �Ӽ� ������ ����
	// ��ġ �Ӽ� (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// �÷� �Ӽ� (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// �ؽ�ó ��ǥ �Ӽ� (u, v)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	// VAO, VBO, EBO ���ε� ���� (�����ϰ�)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	isMeshSet = true;
}

void SpriteComp::Render()
{
	if (!mtex) return;

	mtex->UseTexture();

	// VAO ���ε� �� �׸���
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// ���ε� ����
	glBindVertexArray(0);
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
