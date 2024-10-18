#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
	Camera();
public:

	static Camera* GetInstance()
	{
		static Camera Instace;
		return &Instace;
	}


};