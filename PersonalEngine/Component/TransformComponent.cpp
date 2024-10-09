#include "TransformComponent.h"

#include <gl.h>
#include <iostream>

#include "../ResourceManager/ResourceManager.h"


void TransformComp::CalculateMatrix()
{
    // ���� ��� ��� �ڵ�
    glm::mat4 translateMtx;
    MyMatTranslate(translateMtx, pos);
    glm::mat4 rotaiteMtx;
    MyMatRotate(rotaiteMtx, rot);
    glm::mat4 scaleMtx;
    MyMatScale(scaleMtx, scale);

    // ��� ����
    MyMatConcat(trancsformMatrix, rotaiteMtx, scaleMtx);
    MyMatConcat(trancsformMatrix, translateMtx, trancsformMatrix);

    // ���̴� ���ҽ� ��������
    // ���ϸ� Ȯ���� ���� ����
    Shader* shader = ResourceManager::GetInstance()->GetResource<Shader>("../Extern/Shader/shader.vert");

    if (shader != nullptr)
    {
        // ���̴� Ȱ��ȭ �� ��ȯ ��� ����
        shader->use();
        unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trancsformMatrix));
    }
    else
    {
        std::cerr << "���̴��� �ҷ����� ���߽��ϴ�." << std::endl;
    }
}



TransformComp::TransformComp() :pos({ 0,0,0 }), scale({ 1,1,0 }), rot(0), trancsformMatrix(glm::mat4(1.0f))
{
	CalculateMatrix();
}

TransformComp::TransformComp(GameObject* owner) :pos({ 0,0,0 }), scale({ 1,1,0 }), rot(0), trancsformMatrix(glm::mat4(1.0f))
{
	CalculateMatrix();
}

TransformComp::~TransformComp()
{
}

void TransformComp::Update()
{
	CalculateMatrix();
}

const glm::mat4& TransformComp::GetMatrix() const
{
	return trancsformMatrix;
}

void TransformComp::SetPos(const glm::vec3& otherPos)
{
	pos = otherPos;
}

void TransformComp::SetScale(const glm::vec3& otherScale)
{
	scale = otherScale;
}

void TransformComp::SetRot(const float& otherRot)
{
	rot = otherRot;
}

void TransformComp::PrintMatrix()
{
	std::cout << "Printing Transform Comp. With this values: " << std::endl;
	std::cout << "Translate : " << pos.x << " " << pos.y << std::endl;
	std::cout << "Rotation  : " << rot << std::endl;
	std::cout << "Scale     : " << scale.x << " " << scale.y << std::endl;

	// Print the full 4x4 matrix
	for (int i = 0; i < 4; i++)
	{
		std::cout << " | ";
		for (int x = 0; x < 4; x++) {
			std::cout << " " << trancsformMatrix[i][x];
		}
		std::cout << " |" << std::endl;
	}
}


void TransformComp::LoadFromJson(const json& data)
{
}

json TransformComp::SaveToJson()
{
	return json();
}

BaseRTTI* TransformComp::CreateTransformComp()
{
	return nullptr;
}
