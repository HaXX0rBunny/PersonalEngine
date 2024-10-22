#pragma once
#include <glfw3.h>
#include "EngineState.h"
struct Keystate {


	static GLboolean keystateW;
	static GLboolean keystateS;
	static GLboolean keystateA;
	static GLboolean keystateD;
	static GLboolean keystateF5;
	static GLboolean keystateSpace;
	static void updateKeyState(const int& key, const int& action,const int& targetKey, GLboolean& keyState);
	static void key_callback(GLFWwindow* window,int key,int scancode,int action, int mods);
};