#pragma once
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Serializer/Serializer.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#include "../GSM/GameStateManager.h"
#include "../Component/SpriteComponent.h"
#include "../Component/TransformComponent.h"
class MainMenuEditor {
public:
	static void TopBar();
	static void FileMenu();
	static std::string currentfile;
	char buffer[100] = { 0 };
};
