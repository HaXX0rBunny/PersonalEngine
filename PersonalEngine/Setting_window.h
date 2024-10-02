#pragma once

#include <gl.h>
#include <glfw3.h>

#include <glm.hpp>
#include <stdlib.h>

#include <stdio.h>
#include <fstream>
#include <string>
//
#define Window_width 1600
#define Window_height 800

int setWindow_();
void GameLoop(GLFWwindow* window);
std::string ReadFile(const char* filePath);
GLuint AddShader(const char* shaderCode, GLenum shaderType);
void CompileShader(const char* vsCode, const char* fsCode);
void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath);
void CreateTriangle();