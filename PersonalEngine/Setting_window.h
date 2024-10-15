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


#include "Shader.h"

#include "Level/TestLevel.h"
#include "GSM/GameStateManager.h"
#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/ShaderResource.h"
#include "Serializer/Serializer.h"



#include "../Extern/image/stb_image.h"

#define Window_width 1600
#define Window_height 800

int setWindow_();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GameLoop(GLFWwindow* window, Shader& shader);
