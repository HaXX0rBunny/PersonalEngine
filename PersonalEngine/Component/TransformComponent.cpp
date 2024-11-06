#include "TransformComponent.h"

#include "../GameObjectManager/GameObjectManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../GameObjectManager/GameObjectManager.h"

static void printMtx(const glm::mat4& mat)
{
	// Print the full 4x4 matrix
	for (int i = 0; i < 4; i++)
	{
		std::cout << " | ";
		for (int x = 0; x < 4; x++) {
			std::cout << " " << mat[x][i];
		}
		std::cout << " |" << std::endl;
	}
	std::cout << std::endl;
}

void TransformComp::CalculateMatrix()
{
	DEBUG_PROFILER_START("Transform");
	glm::mat4 translateMtx, rotateMtx, scaleMtx;

	MyMatTranslate(translateMtx, pos);

	MyMatRotate(rotateMtx, rot);

	MyMatScale(scaleMtx, scale);

	//glm::mat4 uWorld_NDC = glm::ortho(-800.0f, 800.f,-400.f,
	//	 400.0f,-1.0f, 1.0f);

	MyMatConcat(trancsformMatrix, translateMtx	, rotateMtx);// translation * rotation
	MyMatConcat(trancsformMatrix, trancsformMatrix, scaleMtx); // (translation * rotation) * scale
	//MyMatConcat(trancsformMatrix, uWorld_NDC, trancsformMatrix);
	DEBUG_PROFILER_END;
}



TransformComp& TransformComp::operator=(const TransformComp& other)
{

	if (this == &other) return *this;  // �ڱ� �ڽŰ��� ���� ����
	pos = other.pos;
	scale = other.scale;
	rot = other.rot;
	trancsformMatrix = other.trancsformMatrix;
	prePos = other.prePos;
	return *this;

}

TransformComp::TransformComp(GameObject* owner) :EngineComponent(owner), pos({ 0,0,0 }), scale({ 100,100,1 }), rot(0), trancsformMatrix(glm::mat4(1.0f)), prePos({ 0,0,0 })
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
	prePos.x = pos.x;
	prePos.y = pos.y;
	prePos.z = pos.z;
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
	prePos = otherPos;
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

glm::vec3 TransformComp::GetPreviousPosition() const
{
	return prePos;
}


void TransformComp::LoadFromJson(const json& data)
{
	auto compData = data.find("CompData");

	if (compData != data.end())
	{
		// Pos �� �ε�
		auto p = compData->find("Pos");
		if (p != compData->end() && p->is_array())
		{
			//std::cout << "Loading Pos: " << (*p)[0] << ", " << (*p)[1] << std::endl;
			pos.x = (*p)[0];
			pos.y = (*p)[1];
		}

		// Scale �� �ε�
		auto s = compData->find("Sca");
		if (s != compData->end() && s->is_array())
		{
			//std::cout << "Loading Scale: " << (*s)[0] << ", " << (*s)[1] << std::endl;
			scale.x = (*s)[0];
			scale.y = (*s)[1];
		}

		// Rot �� �ε�
		auto r = compData->find("Rot");
		if (r != compData->end())
		{
			//std::cout << "Loading Rotation: " << r.value() << std::endl;
			rot = r.value();
		}
	}
	// Data �ε� �� ��Ʈ���� ���
	CalculateMatrix();

}
json TransformComp::SaveToJson()
{
	json data;
	//save the type
	data["Type"] = GetType();
	//Save my data
	json compData;
	//pos
	compData["Pos"] = { pos.x, pos.y };
	//sacle
	compData["Sca"] = { scale.x, scale.y };
	//rot
	compData["Rot"] = rot;
	data["CompData"] = compData;
	return data;
}

BaseRTTI* TransformComp::CreateTransformComp()
{
	GameObject* lastObj = GameObjectManager::Instance()->GetLastObj();

	// lastObj�� nullptr�� ��� ó��
	if (lastObj == nullptr) {
		std::cerr << "Error: No valid GameObject found in GameObjectManager." << std::endl;
		return nullptr;  // Ȥ�� ������ ���� ó��
	}
	BaseRTTI* out = new TransformComp(lastObj);

	std::cout << "TransformComponent 170: Created TransformComp" << out << std::endl;
	return out;
}
