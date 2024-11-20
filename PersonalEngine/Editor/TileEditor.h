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
	const ImVec4 GRID_COLOR = ImVec4(190.5f, 0.5f, 0.5f, 0.3f);
	enum class TileType {
		None,
		Wall,
		Block,
		Player
	};
	TileType currentTileType = TileType::None;
	bool isDragging = false;
	glm::vec2 dragStart;
	glm::vec2 lastTilePos = glm::vec2(-1);

public:
	

	void Update();
	void DrawGrid();
	void CreateTileObject(const glm::vec2& position);
	glm::vec2 SnapToGrid(const glm::vec2& position);
	void ShowTileMenu();

};