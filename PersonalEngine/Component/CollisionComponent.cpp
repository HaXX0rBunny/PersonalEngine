#include "CollisionComponent.h"
#include "../CollsionManager/CollisionManager.h"
#include "../CollsionManager/CollisionEvent.h"
#include "../Event/EventManager.h"
#include <set>
CollisionComp::CollisionComp(GameObject* owner) :EngineComponent(owner), vPos({ 0,0 }), vScale({ 0,0 }),fRot(0),isCollider(false), isVisible(false)
{
	SetCollision();
	vao=0, vbo=0, ebo=0;
	CollisionManager::GetInstance().RegisterCollisionComponent(this);
}

CollisionComp::~CollisionComp()
{
	CollisionManager::GetInstance().UnregisterCollisionComponent(this);
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
	if (ebo != 0)
		glDeleteBuffers(1, &ebo);
}

void CollisionComp::Update() {


	auto allObjects = GameObjectManager::Instance()->AllObj();
	for (auto& obj : allObjects) {
		CollisionComp* other = obj.second->GetComponent<CollisionComp>();
		if (other && other != this && CheckCollision(other)) {
		

				std::cout << "Collision event triggered between "
					<< this->GetOwner()->GetName()
					<< " and "
					<< other->GetOwner()->GetName()
					<< std::endl;

				EventManager::GetInstance()->AddEvent<CollisionEvent>(this, other);
			
		
		}
	}

}
void CollisionComp::OnEvent(Event* event) {
	// 이벤트가 충돌 이벤트인지 확인
	if (CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(event)) {
		// src와 dst가 nullptr이 아닌지 확인
		if (!collisionEvent->src || !collisionEvent->dst) {
			std::cerr << "Invalid source or destination in CollisionEvent." << std::endl;
			return; // 유효하지 않은 경우 처리 중단
		}

		// 충돌한 다른 컴포넌트 확인
		CollisionComp* other = dynamic_cast<CollisionComp*>(collisionEvent->src == this ? collisionEvent->dst : collisionEvent->src);

		if (other) {
			GameObject* otherObject = other->GetOwner();
			GameObject* thisObject = this->GetOwner();
			PlayerComp* playerComp = thisObject->GetComponent<PlayerComp>();

			// PlayerComp가 유효한지 확인
			if (playerComp) {
				// Player와 Wall 사이의 충돌 처리
				if (thisObject->ObjectTag == GameObject::Player && otherObject->ObjectTag == GameObject::Wall) {
					std::cout << "Player와 Wall 충돌 처리!" << std::endl;

					// 플레이어의 위치를 이전 위치로 되돌림
					TransformComp* playerTransform = thisObject->GetComponent<TransformComp>();

					if (playerTransform) {
						glm::vec3 previousPos = playerTransform->GetPreviousPosition();
						playerTransform->SetPos(previousPos);  // 이전 위치로 되돌림
						playerComp->SetCollisionState(true);
					}
				}
				else {
					playerComp->SetCollisionState(false);
				}
			}
		}
	}
}

void CollisionComp::Render()
{
	if (!isVisible) return;  
	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
	//glLineWidth(5.0f);
	glLineWidth(fwidth_Line);

	glBindVertexArray(vao);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0);
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

bool CollisionComp::CheckCollision(const CollisionComp* other) const
{
	const glm::vec3& pos1 = own->GetComponent<TransformComp>()->GetPos();
	const glm::vec3& scale1 = own->GetComponent<TransformComp>()->GetScale();
	const glm::vec3& pos2 = other->own->GetComponent<TransformComp>()->GetPos();
	const glm::vec3& scale2 = other->own->GetComponent<TransformComp>()->GetScale();

	bool collisionX = pos1.x + scale1.x >= pos2.x && pos2.x + scale2.x >= pos1.x;
	bool collisionY = pos1.y + scale1.y >= pos2.y && pos2.y + scale2.y >= pos1.y;

	// 충돌이 발생하는지 디버그 출력
	/*if (collisionX && collisionY) {
		std::cout << "Collision detected between objects." << std::endl;
	}*/

	return collisionX && collisionY;
}
void CollisionComp::SetCollision()
{
	TransformComp* C_TransComp=own->GetComponent<TransformComp>();
	SetPos(C_TransComp->GetPos());
	SetScale(C_TransComp->GetScale());
	SetRot(C_TransComp->GetRot());
}

void CollisionComp::SetCollision(const glm::vec3& vPos_i, const glm::vec3& vScale_i, const float& fRot_i)
{
	SetPos(vPos_i);
	SetScale(vScale_i);
	SetRot(fRot_i);
}

void CollisionComp::SetCollision(const float& fPosx_i, const float& fPosy_i, const float& fScalex_i, const float& fSacaley_i, const float& fRot_i)
{
	SetPos(fPosx_i, fPosy_i);
	SetScale(fScalex_i, fSacaley_i);
	SetRot(fRot_i);
}



void CollisionComp::SetPos(const float& x, const float& y)
{
	vPos.x = x;
	vPos.y = y;
}
void CollisionComp::SetPos(const glm::vec3& vPosi)
{
	vPos.x = vPosi.x;
	vPos.y = vPosi.y;
}
void CollisionComp::SetScale(const float& x, const float& y)
{
	vScale.x = x;
	vScale.y = y;
}

void CollisionComp::SetScale(const glm::vec3& vScalei)
{
	vScale.x = vScalei.x;
	vScale.y = vScalei.y;
}

void CollisionComp::SetRot(const float& fRoti)
{
	fRot = fRoti;
}

void CollisionComp::SetVisible(const bool& cb_in)
{
	isVisible = cb_in;
}



void CollisionComp::LoadFromJson(const json& data) {
	auto compData = data.find("CompData");

	if (compData != data.end()) {
		// Load position
		auto pos = compData->find("Position");
		if (pos != compData->end() && pos->is_array()) {
			vPos.x = (*pos)[0];
			vPos.y = (*pos)[1];
		}

		// Load scale
		auto scale = compData->find("Scale");
		if (scale != compData->end() && scale->is_array()) {
			vScale.x = (*scale)[0];
			vScale.y = (*scale)[1];
		}

		// Load rotation
		auto rotation = compData->find("Rotation");
		if (rotation != compData->end()) {
			fRot = rotation.value();
		}

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
	compData["Position"] = { vPos.x, vPos.y };
	compData["Scale"] = { vScale.x, vScale.y };
	compData["Rotation"] = fRot;
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

	return new CollisionComp(lastObj);  // Return a new CollisionComp instance
}
