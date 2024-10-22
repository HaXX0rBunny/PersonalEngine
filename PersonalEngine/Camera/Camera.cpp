#include "Camera.h"

Camera::Camera() : cameraPosition(0.0f, 0.0f, 0.0f), // 기본 카메라 위치
cameraTarget(0.0f, 0.0f, 0.0f),  // 기본으로 보는 지점 (타겟)
cameraUp(0.0f, 1.0f, 0.0f),
offset(0.0f, 2.0f,10.0f),
zoomLevel(1.0f)
{

	UpdateViewMatrix();
	SetProjectionMatrix(-800.0f, 800.0f, -400.0f, 400.0f, -100.f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::Update() {
	auto playerObj = GameObjectManager::Instance()->GetObj("player");
	if (playerObj != nullptr) {
		auto playerTransform = playerObj->GetComponent<TransformComp>();
		if (playerTransform) {
			glm::vec3 playerPos = playerTransform->GetPos();
			cameraPosition = playerPos + offset;  // 오프셋을 더해 카메라 위치 설정
			cameraTarget = playerPos;
			UpdateViewMatrix();  // 뷰 행렬 업데이트
		}
	}

}


void Camera::SetCameraPosition(const glm::vec3& position)
{
	cameraPosition = position;
	UpdateViewMatrix();
}

void Camera::SetCameraTarget(const glm::vec3& target)
{
	cameraTarget = target;
	UpdateViewMatrix();
}

void Camera::SetCameraUp(const glm::vec3& up)
{
	cameraUp = up;
	UpdateViewMatrix();
}

void Camera::ZoomIn()
{
	zoomLevel -= 0.1f; // Adjust zoom level
	if (zoomLevel < 0.1f) zoomLevel = 0.1f; // Prevent zooming too far in
	SetProjectionMatrix(-800.0f * zoomLevel, 800.0f * zoomLevel, -400.0f * zoomLevel, 400.0f * zoomLevel, -1.0f, 1.0f);

}

void Camera::ZoomOut()
{
	zoomLevel += 0.1f; // Adjust zoom level
	if (zoomLevel > 2.0f) zoomLevel = 2.0f; // Prevent zooming too far out
	SetProjectionMatrix(-800.0f * zoomLevel, 800.0f * zoomLevel, -400.0f * zoomLevel, 400.0f * zoomLevel, -1.0f, 1.0f);

}

void Camera::UpdateViewMatrix()
{
	
	viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
	
}


const glm::mat4& Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::SetProjectionMatrix(float left, float right, float bottom, float top, float nearClip, float farClip)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, nearClip, farClip);
}


const glm::mat4& Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::MoveCamera(const glm::vec3& direction)
{
	cameraPosition += direction;
	UpdateViewMatrix();
}

