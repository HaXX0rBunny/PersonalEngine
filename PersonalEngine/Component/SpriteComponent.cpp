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
		// 기존 텍스처 언로드
		ResourceManager::GetInstance()->UnloadResource(textureName);
	}
	textureName = filepath;

	// 올바른 타입으로 텍스처 가져오기
	mtex = ResourceManager::GetInstance()->GetResource<Texture>(textureName);
	if (mtex != nullptr) {
		isTextureSet = true; // 텍스처가 성공적으로 로드되었음을 표시
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
		// 우측 상단 정점
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // 위치, 컬러, 텍스처 좌표
		// 우측 하단 정점
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // 위치, 컬러, 텍스처 좌표
		// 좌측 하단 정점
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 위치, 컬러, 텍스처 좌표
		// 좌측 상단 정점
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}  // 위치, 컬러, 텍스처 좌표
	};

	// 인덱스 배열을 std::vector로 관리하지 않지만, 정적 배열로 사용
	unsigned int indices[] = {
		0, 1, 3, // 첫 번째 삼각형
		1, 2, 3  // 두 번째 삼각형
	};
	// VAO, VBO, EBO 생성
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// VAO 바인드 (설정을 위해)
	glBindVertexArray(vao);

	// VBO 바인드 및 데이터 전송
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// EBO 바인드 및 데이터 전송
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 정점 속성 포인터 설정
	// 위치 속성 (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// 컬러 속성 (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// 텍스처 좌표 속성 (u, v)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	// VAO, VBO, EBO 바인딩 해제 (안전하게)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	isMeshSet = true;
}

void SpriteComp::Render()
{
	if (!mtex) return;

	mtex->UseTexture();

	// VAO 바인딩 및 그리기
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// 바인딩 해제
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
