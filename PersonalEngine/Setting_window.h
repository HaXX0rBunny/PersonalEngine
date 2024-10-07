#pragma once

#include <gl.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>

#include "Shader.h"
#include <fstream>
#include <string>
#include <iostream>
#pragma warning(push)
#pragma warning(disable : 6262) // 스택 사용 경고 비활성화
#include "../Extern/image/stb_image.h"
#pragma warning(pop)

#define Window_width 1600
#define Window_height 800

int setWindow_();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GameLoop(GLFWwindow* window, Shader& shader);
//std::string ReadFile(const char* filePath);
//GLuint AddShader(const char* shaderCode, GLenum shaderType);
//void CompileShader(const char* vsCode, const char* fsCode);
//void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath);
//void CreateTriangle();
//void CreateRectangle();
void CreateTexture();
void ClearShader();
void ClearBuffer();