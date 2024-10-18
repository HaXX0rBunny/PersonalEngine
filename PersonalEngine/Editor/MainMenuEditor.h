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
#include "../Utility/Filedialog.h"
#include "../Utility/CompareFile.h"

enum SaveState {
	Save,
	Cancel,
	nSave,
	None
};
class MainMenuEditor {
public:
	static void TopBar();
	static void PopupMenu();
	static std::string currentfile;
	static void ShowSavePopup();
	static void InvalidFileDialog();
	static void NewObjectPopup();
	static void RenamePopup();
	static void InvalidImageFileDialog();
	static void StartNewFile();
	static void OpenNewFile(const std::string& openPath);
	static void DragSetObject();
	char buffer[100] = { 0 };
};
