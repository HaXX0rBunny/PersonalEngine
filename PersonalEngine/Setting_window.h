#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#define Window_width 1600
#define Window_height 800
namespace SetWindow{
int setWindow();
void GameLoop(GLFWwindow* window);
}