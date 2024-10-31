#include "CollisionComponent.h"
#include "../CollsionManager/CollisionManager.h"
#include "../Event/EventManager.h"
#include "../ResourceManager/ResourceManager.h"
#include <iostream>
#include <vector>
#include <limits>

CollisionComp::CollisionComp(GameObject* owner)
    : EngineComponent(owner), isCollider(false), isVisible(false), vao(0), vbo(0), ebo(0)
{
    CollisionManager::GetInstance()->RegisterCollisionComponent(this);
	mShader = ResourceManager::GetInstance()->GetResource<Shader>("../Extern/Shader/shader.vert");

	SetCollisionBox();
}

CollisionComp::~CollisionComp()
{
    CollisionManager::GetInstance()->UnregisterCollisionComponent(this);
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (ebo) glDeleteBuffers(1, &ebo);
}

void CollisionComp::Update()
{
	//UpdateTransformMatrix();
    Render();
}

void CollisionComp::OnEvent(Event* event) {
	if (CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(event)) {
		if (!collisionEvent->src || !collisionEvent->dst) {
			std::cerr << "Invalid source or destination in CollisionEvent." << std::endl;
			return;
		}

		CollisionComp* other = dynamic_cast<CollisionComp*>(collisionEvent->src == this ? collisionEvent->dst : collisionEvent->src);
		if (!other) return;

		GameObject* thisObject = this->GetOwner();
		GameObject* otherObject = other->GetOwner();
		PlayerComp* playerComp = thisObject->GetComponent<PlayerComp>();

		if (playerComp && thisObject->ObjectTag == GameObject::Player && otherObject->ObjectTag != GameObject::Player) {
			// 충돌 축 계산 및 적용
			const glm::mat4& playerMatrix = thisObject->GetComponent<TransformComp>()->GetMatrix();
			const glm::mat4& otherMatrix = otherObject->GetComponent<TransformComp>()->GetMatrix();
			std::vector<glm::vec3> axes = CalculateAxes(playerMatrix, otherMatrix);

			// 충돌 감지 및 처리
			glm::vec3 smallestAxis;
			float minOverlap;
			bool collisionDetected = DetectCollision(playerMatrix, otherMatrix, axes, smallestAxis, minOverlap);

			if (collisionDetected) {
				glm::vec3 playerPos = thisObject->GetComponent<TransformComp>()->GetPos();
				glm::vec3 moveDirection = glm::normalize(smallestAxis) * minOverlap;
				playerPos += (glm::dot(playerPos - otherObject->GetComponent<TransformComp>()->GetPos(), smallestAxis) > 0 ? 1.0f : -1.0f) * moveDirection;

				thisObject->GetComponent<TransformComp>()->SetPos(playerPos);
				playerComp->SetCollisionState(true);
			}
			else {
				playerComp->SetCollisionState(false);
			}
		}
	}
}

std::vector<glm::vec3> CollisionComp::CalculateAxes(const glm::mat4& playerMatrix, const glm::mat4& otherMatrix) const {
	return {
		glm::normalize(glm::vec3(playerMatrix[0])),
		glm::normalize(glm::vec3(playerMatrix[1])),
		glm::normalize(glm::vec3(otherMatrix[0])),
		glm::normalize(glm::vec3(otherMatrix[1]))
	};
}

bool CollisionComp::DetectCollision(
	const glm::mat4& matrix1, const glm::mat4& matrix2,
	const std::vector<glm::vec3>& axes, glm::vec3& smallestAxis, float& minOverlap) const {
	minOverlap = std::numeric_limits<float>::max();

	for (const auto& axis : axes) {
		float min1, max1, min2, max2;
		ProjectOntoAxis(matrix1, axis, min1, max1);
		ProjectOntoAxis(matrix2, axis, min2, max2);

		if (max1 < min2 || max2 < min1) {
			return false;  // 겹침이 없는 축이 있으면 충돌이 아님
		}
		else {
			float overlap = std::min(max1, max2) - std::max(min1, min2);
			if (overlap < minOverlap) {
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}
	}
	return true;  // 모든 축에서 겹침이 발생하면 충돌임
}

void CollisionComp::ProjectOntoAxis(const glm::mat4& transform, const glm::vec3& axis, float& min, float& max) const {
	std::vector<glm::vec3> vertices = {
		glm::vec3(transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f)),
		glm::vec3(transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f)),
		glm::vec3(transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f)),
		glm::vec3(transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f))
	};

	min = max = glm::dot(vertices[0], axis);
	for (const auto& vertex : vertices) {
		float projection = glm::dot(vertex, axis);
		min = std::min(min, projection);
		max = std::max(max, projection);
	}
}

glm::mat4 CollisionComp::CreateTransformMatrix(const TransformComp* transform) const
{
    if (!transform) return glm::mat4(1.0f);

    glm::vec3 position = transform->GetPos();
    glm::vec3 scale = transform->GetScale();
    float rotation = glm::radians(transform->GetRot());

    return glm::translate(glm::mat4(1.0f), position) *
        (rotation != 0.0f ? glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1)) : glm::mat4(1.0f)) *
        glm::scale(glm::mat4(1.0f), scale);
}

void CollisionComp::Render()
{



	//glLineWidth(fwidth_Line);

	// VAO 바인딩
	glBindVertexArray(vao);

	// 셰이더 프로그램 사용
	mShader->use(); // 셰이더 프로그램 활성화
	mShader->setBool("useTexture", false);
	// 변환 매트릭스 가져오기
	glm::mat4 transformMatrix = own->GetComponent<TransformComp>()->GetMatrix();

	// 변환 매트릭스를 셰이더로 전송
	unsigned int transformLoc = glGetUniformLocation(mShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	// 충돌 박스 그리기

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0); // 4개의 선 * 2개의 삼각형 * 3개의 정점

	// VAO 바인딩 해제
	glBindVertexArray(0);
}




void CollisionComp::SetVisible(const bool& cb_in)
{
    isVisible = cb_in;
}


void CollisionComp::SetCollisionBox()
{
	//if (!isVisible) return;
	if (vao != 0) return;
	std::vector<Vertex> vertices;
	float offset = fwidth_Line * 0.01f;

	// 외곽선을 그리기 위한 사각형들 (두꺼운 선을 표현하기 위해)
	// 왼쪽 선
	vertices.push_back({ {-0.5f - offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} }); // 좌하단
	vertices.push_back({ {-0.5f - offset,  0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} }); // 좌상단
	vertices.push_back({ {-0.5f + offset,  0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} }); // 우상단
	vertices.push_back({ {-0.5f + offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} }); // 우하단

	// 상단 선
	vertices.push_back({ {-0.5f - offset, 0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ {-0.5f - offset, 0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ { 0.5f + offset, 0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ { 0.5f + offset, 0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });

	// 오른쪽 선
	vertices.push_back({ {0.5f - offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ {0.5f - offset,  0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ {0.5f + offset,  0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ {0.5f + offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });

	// 하단 선
	vertices.push_back({ {-0.5f - offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ {-0.5f - offset, -0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ { 0.5f + offset, -0.5f + offset, 0.0f}, {0.0f, 1.0f, 0.0f} });
	vertices.push_back({ { 0.5f + offset, -0.5f - offset, 0.0f}, {0.0f, 1.0f, 0.0f} });

	// 각 사각형을 그리기 위한 인덱스
	std::vector<GLuint> indices;
	for (int i = 0; i < 4; ++i) // 4개의 선
	{
		int base = i * 4;
		// 각 선마다 두 개의 삼각형
		indices.push_back(base + 0);
		indices.push_back(base + 1);
		indices.push_back(base + 2);

		indices.push_back(base + 0);
		indices.push_back(base + 2);
		indices.push_back(base + 3);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

}
bool CollisionComp::CheckCollision(const CollisionComp* other) const {
	glm::mat4 transform1 = own->GetComponent<TransformComp>()->GetMatrix();
	glm::mat4 transform2 = other->own->GetComponent<TransformComp>()->GetMatrix();

	std::vector<glm::vec3> axes = {
		glm::normalize(glm::vec3(transform1[0])),
		glm::normalize(glm::vec3(transform1[1])),
		glm::normalize(glm::vec3(transform2[0])),
		glm::normalize(glm::vec3(transform2[1]))
	};

	for (const auto& axis : axes) {
		float min1, max1, min2, max2;

		ProjectOntoAxis(transform1, axis, min1, max1);
		ProjectOntoAxis(transform2, axis, min2, max2);

		if (max1 < min2 || max2 < min1) {
			return false; // 충돌 없음
		}
	}
	return true; // 충돌 발생
}
void CollisionComp::ProjectOntoAxis(const glm::vec3& pos, const glm::vec3& scale, float rot, const glm::vec3& axis, float& min, float& max) const {
	std::vector<glm::vec3> vertices;
	if (rot != 0.0f) {
		vertices = {
			pos + glm::vec3(glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(scale.x / 2, scale.y / 2, 0.0f, 1.0f)),
			pos + glm::vec3(glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(scale.x / 2, -scale.y / 2, 0.0f, 1.0f)),
			pos + glm::vec3(glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(-scale.x / 2, -scale.y / 2, 0.0f, 1.0f)),
			pos + glm::vec3(glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(-scale.x / 2, scale.y / 2, 0.0f, 1.0f))
		};
	}
	else {
		vertices = {
			pos + glm::vec3(scale.x / 2, scale.y / 2, 0.0f),
			pos + glm::vec3(scale.x / 2, -scale.y / 2, 0.0f),
			pos + glm::vec3(-scale.x / 2, -scale.y / 2, 0.0f),
			pos + glm::vec3(-scale.x / 2, scale.y / 2, 0.0f)
		};
	}

	min = max = glm::dot(vertices[0], axis);
	for (const auto& vertex : vertices) {
		float projection = glm::dot(vertex, axis);
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}
}

void CollisionComp::LoadFromJson(const json& data) {
	auto compData = data.find("CompData");

	if (compData != data.end()) {
		// Load position
		

		// Load collider and visibility state
		auto collider = compData->find("isCollider");
		if (collider != compData->end()) {
			isCollider = collider.value();
		}

		auto visible = compData->find("isVisible");
		if (visible != compData->end()) {
			isVisible = visible.value();
		}
	}
}

json CollisionComp::SaveToJson() {
	json data;
	data["Type"] = GetType();  // Save the component type
	json compData;
	
	compData["isCollider"] = isCollider;
	compData["isVisible"] = isVisible;
	data["CompData"] = compData;  // Save component-specific data
	return data;
}

BaseRTTI* CollisionComp::CreateCollisionComp() {
	GameObject* lastObj = GameObjectManager::Instance()->GetLastObj();
	if (!lastObj) {
		return nullptr;  // Handle missing GameObject
	}
	BaseRTTI* out = new CollisionComp(lastObj);  // Return a new CollisionComp instance
	return out;
}
