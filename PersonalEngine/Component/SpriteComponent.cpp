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
	// �ùٸ� Ÿ������ �ؽ�ó ��������
	mtex = ResourceManager::GetInstance()->GetResource<Texture>(textureName);
	if (!mtex ) {
		// ���ҽ��� �ùٸ��� �ε���� �ʾ��� ��� ó��
		std::cerr << "Failed to load texture: " << textureName << std::endl;
		return;
	}
	if (mtex != nullptr) {
		isTextureSet = true; // �ؽ�ó�� ���������� �ε�Ǿ����� ǥ��
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
		// ���� ��� ����
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� �ϴ� ����
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� �ϴ� ����
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // ��ġ, �÷�, �ؽ�ó ��ǥ
		// ���� ��� ����
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}  // ��ġ, �÷�, �ؽ�ó ��ǥ
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mShader->use();
	mShader->use();
	mtex->UseTexture();
	// ���̴� ���ҽ� ��������
	// ���ϸ� Ȯ���� ���� ����
	/*���⼭ ���ִ� ������ �� ��ü�� ���̴��� ��� ������ ������ �̷�� ������ 
	���� ���� Ʈ������ ������ �������� ���� �������� ��ǥ�� �ٲ�� �׸����� ���� ���̴��� ���� ������
	�� ���̴��� ������ �̷����� �� �������� �׷����� ��
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
	// ���ε� ����
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
		return nullptr;  // Ȥ�� ������ ���� ó��
	}

	BaseRTTI* out = new SpriteComp(lastObj);

	std::cout << "SpriteComponent 222: Created SpriteComp" << out << std::endl;
	return out;
}
