#pragma once

#include <gl.h>
#include <glfw3.h>

#include <imgui/implot.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>

#include "Shader.h"
#include <fstream>
#include <iostream>
#include "Utility/Time.h"

#include "Shader.h"

#include "Level/TestLevel.h"

#include "GSM/GameStateManager.h"
#include "GameEditorManager/GameEditorManager.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/ShaderResource.h"
#include "Serializer/Serializer.h"
#include "Utility/InputProcess.h"

#include "Camera/Camera.h"
#include "../Extern/image/stb_image.h"
#include "Utility/WindowFigure.h"
//Todo Struct 
#define Window_width 1600
#define Window_height 800
#define EngineTitle "Biginner"

struct SetWindow
{

	static GSM::GameStateManager* gsm;
	static GEM::GameEditorManager* gem;

	static int gGameRunning;


	static int setWindow_();
	static void init();
	static void draw(Shader& shader);
	static void cleanup();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void GameLoop(GLFWwindow* window);
};