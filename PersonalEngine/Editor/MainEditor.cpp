#include "MainEditor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include "../GameObjectManager/GameObjectManager.h"
void MainEditor::TopBar()
{
	ImGui::BeginMainMenuBar();
	ImGui::Text("This is the main menu %i", 56);
	if(ImGui::BeginMenu("New GameObjcet"));
	{
		ImGui::Text("New Game Object Menu");

		ImGui::InputText("GO Name",buffer, 100 );
		if (ImGui::Button("Create"))
		{
			GameObjectManager::Instance()->AllObj();
		}
		ImGui::EndMenu();
	}
}
