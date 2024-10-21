#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
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

	void Seton();
};