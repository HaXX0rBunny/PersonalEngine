#include "Camera.h"

Camera::Camera()
    : cameraPosition(0.0f, 0.0f, 0.0f),
    cameraTarget(0.0f, 0.0f, 0.0f),
    cameraUp(0.0f, 1.0f, 0.0f),
    offset(0.0f, 2.0f, 10.0f),
    zoomLevel(1.0f)
{
    UpdateViewMatrix();
    SetProjectionMatrix(kDefaultLeft, kDefaultRight, kDefaultBottom, kDefaultTop, kDefaultNearClip, kDefaultFarClip);
}

Camera::~Camera() {}

void Camera::Update() {
    auto playerObj = GameObjectManager::Instance()->GetObj("player");
    if (playerObj != nullptr) {
        auto playerTransform = playerObj->GetComponent<TransformComp>();
        if (playerTransform) {
            glm::vec3 playerPos = playerTransform->GetPos();
            SetCameraPosition(playerPos + offset);  // 카메라 위치 업데이트 시 자동으로 뷰 행렬 업데이트
            SetCameraTarget(playerPos);  // 카메라 타겟 업데이트 시 자동으로 뷰 행렬 업데이트
        }
    }
}

void Camera::SetCameraPosition(const glm::vec3& position) {
    if (cameraPosition != position) {
        cameraPosition = position;
        UpdateViewMatrix();
    }
}

void Camera::SetCameraTarget(const glm::vec3& target) {
    if (cameraTarget != target) {
        cameraTarget = target;
        UpdateViewMatrix();
    }
}

void Camera::SetCameraUp(const glm::vec3& up) {
    if (cameraUp != up) {
        cameraUp = up;
        UpdateViewMatrix();
    }
}

void Camera::ZoomIn() {
    SetZoomLevel(zoomLevel - kZoomStep);
}

void Camera::ZoomOut() {
    SetZoomLevel(zoomLevel + kZoomStep);
}

void Camera::SetZoomLevel(float newZoomLevel) {
    if (newZoomLevel < kMinZoomLevel) newZoomLevel = kMinZoomLevel;
    if (newZoomLevel > kMaxZoomLevel) newZoomLevel = kMaxZoomLevel;

    if (zoomLevel != newZoomLevel) {
        zoomLevel = newZoomLevel;
        SetProjectionMatrix(kDefaultLeft * zoomLevel, kDefaultRight * zoomLevel, kDefaultBottom * zoomLevel, kDefaultTop * zoomLevel, -1.0f, 1.0f);
    }
}

void Camera::UpdateViewMatrix() {
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

const glm::mat4& Camera::GetViewMatrix() {
    return viewMatrix;
}

void Camera::SetProjectionMatrix(float left, float right, float bottom, float top, float nearClip, float farClip) {
    projectionMatrix = glm::ortho(left, right, bottom, top, nearClip, farClip);
}

const glm::mat4& Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

void Camera::MoveCamera(const glm::vec3& direction) {
    SetCameraPosition(cameraPosition + direction);
}