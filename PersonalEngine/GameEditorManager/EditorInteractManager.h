#pragma once
#include <vector>
#include "../GameEditorManager/BaseEditor.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/TransformComponent.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glm.hpp>
#include "../Utility/InputProcess.h"
class EditorInteractManager
{
	
	EditorInteractManager();
public:
	static EditorInteractManager* GetInstance()
	{
		static EditorInteractManager Instance;
		return &Instance;
	};
	
	void Update();
	void CheckObject();
	void CheckMouseToCollision(const glm::vec2& CVmousePos_in);
};