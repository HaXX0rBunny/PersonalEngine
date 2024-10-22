#include "CollisionComponent.h"

CollisionComp::CollisionComp(GameObject* owner) :EngineComponent(owner), vPos({ 0,0 }), vScale({ 0,0 }),fRot(0),isCollider(false), isVisible(false)
{
	SetCollision();
	vao=0, vbo=0, ebo=0;
}

CollisionComp::~CollisionComp()
{
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
	if (ebo != 0)
		glDeleteBuffers(1, &ebo);
}

void CollisionComp::Update()
{
	Render();
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




