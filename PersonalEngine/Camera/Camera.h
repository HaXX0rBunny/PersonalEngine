#pragma once
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../GameObjectManager/GameObjectManager.h"
#include "../Component/TransformComponent.h"
#include "../Component/PlayerComponent.h"
constexpr float kDefaultLeft = -800.0f;
constexpr float kDefaultRight = 800.0f;
constexpr float kDefaultBottom = -400.0f;
constexpr float kDefaultTop = 400.0f;
constexpr float kDefaultNearClip = -100.0f;
constexpr float kDefaultFarClip = 100.0f;
constexpr float kMinZoomLevel = 0.1f;
constexpr float kMaxZoomLevel = 2.0f;
constexpr float kZoomStep = 0.1f;
class Camera
{
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
	glm::vec3 offset;
	float zoomLevel;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Camera();


	Camera(const Camera& other) = delete;
	const Camera& operator=(const Camera& other) = delete;
	~Camera();
public:

	static Camera* GetInstance()
	{
		static Camera Instace;
		return &Instace;
	}
	void Update();
	void SetCameraPosition(const glm::vec3& position);
	void SetCameraTarget(const glm::vec3& target);
	void SetCameraUp(const glm::vec3& up);

	// Zoom in/out
	void ZoomIn();
	void ZoomOut();
	void SetZoomLevel(float newZoomLevel);
	const float& getZoom() { return zoomLevel; };
	void UpdateViewMatrix();
	const glm::mat4& GetViewMatrix(); 



		// 투영 행렬 설정
	void SetProjectionMatrix(float left, float right, float bottom, float top, float nearClip, float farClip);

	// 투영 행렬 가져오기
	const glm::mat4& GetProjectionMatrix(); 

	// Additional methods to move the camera
	void MoveCamera(const glm::vec3& direction);

};