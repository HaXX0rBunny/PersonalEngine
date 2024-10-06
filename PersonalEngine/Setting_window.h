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
#define STB_IMAGE_IMPLEMENTATION// 헤더 파일을 관련된 정의 소스 코드만 포함하도록 하여 헤더 파일을 효과적으로 .cpp 파일로 변환
#include "../Extern/image/stb_image.h" // 싱글 헤더 이미지로드 라이브러리 stbi_load
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
void CreateTriangle();
void CreateRectangle();
void CreateTexture();
void ClearShader();
void ClearBuffer();