#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Shader.h"
#include "../ResourceManager/ResourceManager.h"
#include <vector>
#include"../GameObject/GameObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
class TileEditor
{
	bool isEnabled = false;

	const float TILE_SIZE = 40.0f; // 타일 한 칸의 크기
	const ImVec4 GRID_COLOR = ImVec4(0.5f, 0.5f, 0.5f, 0.3f);

public:
	

	void Update();
	void DrawGrid();

};