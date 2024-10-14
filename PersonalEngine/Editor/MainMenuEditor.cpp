#include "MainMenuEditor.h"

void MainMenuEditor::TopBar()
{
	ImGui::BeginMainMenuBar();
	//ImGui::Text("This is the main menu %i", 56);
	if(ImGui::BeginMenu("File"))
	{
		ImGui::Text("New File Menu");

	
		if (ImGui::Button("Load"))
		{
			ImGui::Text("Input Name");
		
			Serializer::Instance()->LoadLevel("test.json");
		}
		if (ImGui::Button("Save"))
		{

			if (ImGui::BeginMenu("Save"))
			{
				ImGui::Text("Input Name");

				Serializer::Instance()->SaveLevel("test.json");
			}
			ImGui::EndMenu();
		}
		if (ImGui::Button("Save as"))
		{
			//GameObjectManager::Instance()->AllObj();
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::Text("New Game Object Menu");

	
		if (ImGui::Button("New Object"))
		{
			for (auto it = GameObjectManager::Instance()->AllObj().begin(); it != GameObjectManager::Instance()->AllObj().end(); it++)
			{
				//ImGui::Text(it->first().c_str);  // 모든 객체 삭제
			}
		}
		if (ImGui::Button("All Object"))
		{
			GameObjectManager::Instance()->AllObj();
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::Text("New Game Object Menu");

		if (ImGui::Button("Create"))
		{
			GameObjectManager::Instance()->AllObj();
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("New Object"))
	{
		ImGui::Text("New Game Object Menu");


		if (ImGui::Button("Create"))
		{
			GameObjectManager::Instance()->AllObj();
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}

void MainMenuEditor::FileMenu()
{
}

