#include "CollisionComponent.h"
#include "../CollsionManager/CollisionManager.h"
#include "../Event/EventManager.h"
#include <iostream>
#include <vector>
#include <limits>

CollisionComp::CollisionComp(GameObject* owner)
    : EngineComponent(owner), isCollider(false), isVisible(false), vao(0), vbo(0), ebo(0)
{
    CollisionManager::GetInstance()->RegisterCollisionComponent(this);
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
    Render();
}

void CollisionComp::OnEvent(Event* event)
{
    if (CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(event)) {
        if (!collisionEvent->src || !collisionEvent->dst) {
            std::cerr << "Invalid source or destination in CollisionEvent." << std::endl;
            return;
        }

        CollisionComp* other = dynamic_cast<CollisionComp*>(collisionEvent->src == this ? collisionEvent->dst : collisionEvent->src);
        if (other) {
            GameObject* thisObject = this->GetOwner();
            GameObject* otherObject = other->GetOwner();
            PlayerComp* playerComp = thisObject->GetComponent<PlayerComp>();

            if (playerComp && thisObject->ObjectTag == GameObject::Player && otherObject->ObjectTag != GameObject::Player) {
                TransformComp* playerTransform = thisObject->GetComponent<TransformComp>();
                TransformComp* otherTransform = otherObject->GetComponent<TransformComp>();

                glm::mat4 playerMatrix = CreateTransformMatrix(playerTransform);
                glm::mat4 otherMatrix = CreateTransformMatrix(otherTransform);

                std::vector<glm::vec3> axes = {
                    glm::normalize(glm::vec3(playerMatrix[0])),
                    glm::normalize(glm::vec3(playerMatrix[1])),
                    glm::normalize(glm::vec3(otherMatrix[0])),
                    glm::normalize(glm::vec3(otherMatrix[1]))
                };

                float minOverlap = std::numeric_limits<float>::max();
                glm::vec3 smallestAxis;
                bool collisionDetected = true;

                for (const auto& axis : axes) {
                    float min1, max1, min2, max2;
                    ProjectOntoAxis(playerMatrix, axis, min1, max1);
                    ProjectOntoAxis(otherMatrix, axis, min2, max2);

                    if (max1 < min2 || max2 < min1) {
                        collisionDetected = false;
                        break;
                    }
                    else {
                        float overlap = std::min(max1, max2) - std::max(min1, min2);
                        if (overlap < minOverlap) {
                            minOverlap = overlap;
                            smallestAxis = axis;
                        }
                    }
                }

                if (collisionDetected) {
                    glm::vec3 playerPos = playerTransform->GetPos();
                    glm::vec3 moveDirection = glm::normalize(smallestAxis) * minOverlap;
                    playerPos += (glm::dot(playerPos - otherTransform->GetPos(), smallestAxis) > 0 ? 1.0f : -1.0f) * moveDirection;
                    playerTransform->SetPos(playerPos);

                    playerComp->SetCollisionState(true);
                }
                else {
                    playerComp->SetCollisionState(false);
                }
            }
        }
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
    if (!isVisible) return;
    glLineWidth(fwidth_Line);
    glBindVertexArray(vao);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void CollisionComp::SetVisible(const bool& cb_in)
{
    isVisible = cb_in;
}


void CollisionComp::SetCollisionBox()
{
	if (vao != 0) return;
	std::vector<Vertex> vertices = {
		// 우측 상단 정점
		{{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // 위치, 컬러
		// 우측 하단 정점
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // 위치, 컬러
		// 좌측 하단 정점
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // 위치, 컬러
		// 좌측 상단 정점
		{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}  // 위치, 컬러
	};
	glm::mat4 Mat4 = { 1.0f };
	if (own->GetComponent<TransformComp>() != nullptr)
		glm::mat4 Mat4 = own->GetComponent<TransformComp>()->GetMatrix();
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 pos(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2]);
		glm::vec4 transformedPos = Mat4 * glm::vec4(pos, 1.0f);

		vertices[i].position[0] = transformedPos.x;
		vertices[i].position[1] = transformedPos.y;
		vertices[i].position[2] = transformedPos.z;
	}

	unsigned int indices[] = { 0, 1, 2, 3 };

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// VAO 바인드
	glBindVertexArray(vao);

	// VBO 바인드 및 데이터 전송
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// EBO 바인드 및 데이터 전송
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 정점 속성 포인터 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}
bool CollisionComp::CheckCollision(const CollisionComp* other) const {
	TransformComp* tComp1 = own->GetComponent<TransformComp>();
	TransformComp* tComp2 = other->own->GetComponent<TransformComp>();

	if (!tComp1 || !tComp2) return false;

	glm::vec3 pos1 = tComp1->GetPos();
	glm::vec3 scale1 = tComp1->GetScale();
	float rot1 = glm::radians(tComp1->GetRot());

	glm::vec3 pos2 = tComp2->GetPos();
	glm::vec3 scale2 = tComp2->GetScale();
	float rot2 = glm::radians(tComp2->GetRot());

	// 회전 변환 적용한 매트릭스 생성
	glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), pos1) * glm::rotate(glm::mat4(1.0f), rot1, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), scale1);
	glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), pos2) * glm::rotate(glm::mat4(1.0f), rot2, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), scale2);

	// 각 상자의 축 벡터
	std::vector<glm::vec3> axes = {
		glm::normalize(glm::vec3(transform1[0])),
		glm::normalize(glm::vec3(transform1[1])),
		glm::normalize(glm::vec3(transform2[0])),
		glm::normalize(glm::vec3(transform2[1]))
	};

	for (const auto& axis : axes) {
		float min1, max1, min2, max2;

		// 첫 번째 상자 투영
		ProjectOntoAxis(pos1, scale1, rot1, axis, min1, max1);

		// 두 번째 상자 투영
		ProjectOntoAxis(pos2, scale2, rot2, axis, min2, max2);

		if (max1 < min2 || max2 < min1) {
			return false;  // 충돌 없음
		}
	}
	return true;  // 모든 축에서 충돌이 발생하는 경우
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
