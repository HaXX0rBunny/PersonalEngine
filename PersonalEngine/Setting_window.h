#pragma once

#include <gl.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>


#include <fstream>
#include <string>
#include <iostream>
//
#define Window_width 1600
#define Window_height 800

int setWindow_();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GameLoop(GLFWwindow* window);
std::string ReadFile(const char* filePath);
GLuint AddShader(const char* shaderCode, GLenum shaderType);
void CompileShader(const char* vsCode, const char* fsCode);
void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath);
void CreateTriangle();
void ClearShader();