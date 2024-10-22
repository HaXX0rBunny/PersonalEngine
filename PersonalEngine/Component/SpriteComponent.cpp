#include "SpriteComponent.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Utility/MyTexture.h"
#include "TransformComponent.h"
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
SpriteComp::SpriteComp(GameObject* owner) :GraphicsComponent(owner), Alpha(1.0f), mtex(nullptr), isMeshSet(false), isTextureSet(false)
{
	mShader = ResourceManager::GetInstance()->GetResource<Shader>("../Extern/Shader/shader.vert");

	vao = 0;
	vbo = 0;
	ebo = 0;
	mColor = {1,1,1};

}

SpriteComp::~SpriteComp()
{

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void SpriteComp::Update()
{
	
	std::string name = textureName;
	if (isMeshSet&& isTextureSet) 
		Render();
	
}

void SpriteComp::SetTexture(const std::string& filepath)
{
	if (textureName != filepath)
	{	
		ResourceManager::GetInstance()->UnloadResource(textureName);
	}

	textureName = filepath;
	if (filepath == "")
	{
		textureName = "./Assets/Default.png";
	}
	// 올바른 타입으로 텍스처 가져오기
	mtex = ResourceManager::GetInstance()->GetResource<Texture>(textureName);
	if (!mtex ) {
		// 리소스가 올바르게 로드되지 않았을 경우 처리
		std::cerr << "Failed to load texture: " << textureName << std::endl;
		return;
	}
	if (mtex != nullptr) {
		isTextureSet = true; // 텍스처가 성공적으로 로드되었음을 표시
	}
	SetMesh();
}


void SpriteComp::SetAlpha(const float& a)
{
	Alpha = a;
}

float SpriteComp::GetAlpha()
{
	return Alpha;
}

void SpriteComp::SetColor(const float& r, const float& g, const float& b)
{
	mColor.r= r;
	mColor.g = g;
	mColor.b = b;
}

void SpriteComp::SetColor(const glm::vec3& other)
{
	mColor = other;
}

void SpriteComp::SetMesh()
{

	std::vector<Vertex> vertices = {
		// 우측 상단 정점
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 위치, 컬러, 텍스처 좌표
		// 우측 하단 정점
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // 위치, 컬러, 텍스처 좌표
		// 좌측 하단 정점
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // 위치, 컬러, 텍스처 좌표
		// 좌측 상단 정점
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}  // 위치, 컬러, 텍스처 좌표
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mShader->use();
	mShader->use();
	mtex->UseTexture();
	// 셰이더 리소스 가져오기
	// 파일명에 확장자 없이 전달
	/*여기서 해주는 이유는 각 객체의 쉐이더가 사용 됬을때 변형이 이루어 져야함 
	이전 같이 트랜스폼 컴포에 했을때는 생성 됬을때만 좌표가 바뀌고 그릴때는 같은 쉐이더를 쓰기 때문에
	한 쉐이더로 변형이 이뤄져서 맨 마지막만 그려지는 것
	*/

	unsigned int colorLoc = glGetUniformLocation(mShader->ID, "spriteColor");
	glUniform4f(colorLoc, mColor.r, mColor.g, mColor.b, Alpha);
	unsigned int transformLoc = glGetUniformLocation(mShader->ID, "transform");
	if (own->GetComponent<TransformComp>() == nullptr)
	{
		glm::vec4 defaultMat{ 1.0f };
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(defaultMat));
		
	}
	else
	{
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(own->GetComponent<TransformComp>()->GetMatrix()));
		//std::cout << own->GetComponent<TransformComp>() << std::endl;
		//own->GetComponent<TransformComp>()->PrintMatrix();
	}

	glm::mat4 viewMatrix = Camera::GetInstance()->GetViewMatrix();
	glm::mat4 projectionMatrix = Camera::GetInstance()->GetProjectionMatrix();

	unsigned int viewLoc = glGetUniformLocation(mShader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	unsigned int projectionLoc = glGetUniformLocation(mShader->ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisable(GL_BLEND);
	// 바인딩 해제
	glBindVertexArray(0);
	glUseProgram(0);

}

void SpriteComp::LoadFromJson(const json& data)
{
	auto compData = data.find("CompData");

	if (compData != data.end())
	{
		auto c = compData->find("Color");
		mColor.r = c->begin().value();
		mColor.g = (c->begin() + 1).value();
		mColor.b = (c->begin() + 2).value();

		auto a = compData->find("Alpha");
		Alpha = a->begin().value();

		auto f = compData->find("TextureName");
		textureName = f->begin().value();
		SetTexture(textureName);
	}
}

json SpriteComp::SaveToJson()
{

	json data;
	data["Type"] = GetType();
	json compData;
	
	compData["Color"] = {mColor.r, mColor.g, mColor.b};

	compData["Alpha"] = Alpha;

	compData["TextureName"] = textureName;
	data["CompData"] = compData;
	return data;
}

BaseRTTI* SpriteComp::CreateSpriteComp()
{
	GameObject* lastObj = GameObjectManager::Instance()->GetLastObj();
	if (lastObj == nullptr) {
		std::cerr << "Error: No valid GameObject found in GameObjectManager." << std::endl;
		return nullptr;  // 혹은 적절한 예외 처리
	}

	BaseRTTI* out = new SpriteComp(lastObj);

	std::cout << "SpriteComponent 222: Created SpriteComp" << out << std::endl;
	return out;
}
