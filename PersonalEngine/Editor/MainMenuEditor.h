#pragma once
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Serializer/Serializer.h"
#include "../GameObjectManager/GameObjectManager.h"
class MainMenuEditor {
public:
	static void TopBar();
	static void FileMenu();
	char buffer[100] = { 0 };
};
