#pragma once

#include <gl.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>
#include "Editor/MainMenuEditor.h"
#include "Shader.h"
#include <fstream>
#include <iostream>
#include "Utility/Time.h"

#include "Shader.h"

#include "Level/TestLevel.h"
#include "GSM/GameStateManager.h"
#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/ShaderResource.h"
#include "Serializer/Serializer.h"
#include "Utility/InputProcess.h"


#include "../Extern/image/stb_image.h"

//Todo Struct 

struct SetWindow
{
#define Window_width 1600
#define Window_height 800
#define EngineTitle "Biginner"

	static GSM::GameStateManager* gsm;
	static GLFWwindow* window ;
	static int gGameRunning;
	
	static GLint width, height;
	static std::string title;

	static int setWindow_();
	static void init(GLint width, GLint height, std::string title);
	static void draw(Shader& shader);
	static void cleanup();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void GameLoop(GLFWwindow* window);
};