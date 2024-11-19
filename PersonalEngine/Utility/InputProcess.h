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
	static GLboolean keystateLBtn;
	static GLboolean keystateRBtn;
	static GLboolean keystateQ;

	static GLboolean keystateE;
	static GLboolean keystateUp;
	static GLboolean keystateLeft;
	static GLboolean keystateDown;
	static GLboolean keystateRight;
	static GLboolean keystateRShift;
	static GLboolean keystateF9;
	static GLboolean keystateF1;
	static GLboolean keystateF2;
	static void updateKeyState(const int& key, const int& action,const int& targetKey, GLboolean& keyState);
	static void updateMouseKeyState(const int& key, const int& action, const int& targetKey, GLboolean& keyState);
	static void key_callback(GLFWwindow* window,int key,int scancode,int action, int mods);
};