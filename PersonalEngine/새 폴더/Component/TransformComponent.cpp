#include "TransformComponent.h"

#include <gl.h>
#include <iostream>

#include "../ResourceManager/ResourceManager.h"


void TransformComp::CalculateMatrix()
{
	glm::mat4 translateMtx, rotateMtx, scaleMtx;
	MyMatTranslate(translateMtx, pos);
	MyMatRotate(rotateMtx, rot);
	MyMatScale(scaleMtx, scale);

	glm::mat4 uWorld_NDC = glm::ortho(-800.0f, 800.f,400.f,
		 -400.0f,-1.0f, 1.0f);


	MyMatConcat(trancsformMatrix, rotateMtx, scaleMtx);
	MyMatConcat(trancsformMatrix, translateMtx, trancsformMatrix);
	MyMatConcat(trancsformMatrix, uWorld_NDC, trancsformMatrix);

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
	
}

const glm::mat4& TransformComp::GetMatrix() const
{
	return trancsformMatrix;
}

void TransformComp::SetPos(const float& x, const float& y, const float& z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	CalculateMatrix();
}

void TransformComp::SetScale(const float& x, const float& y, const float& z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	CalculateMatrix();
}

void TransformComp::SetPos(const glm::vec3& otherPos)
{
	pos = otherPos;
	CalculateMatrix();
}

void TransformComp::SetScale(const glm::vec3& otherScale)
{
	scale = otherScale;
	CalculateMatrix();
}

void TransformComp::SetRot(const float& otherRot)
{
	rot = otherRot;
	CalculateMatrix();
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
