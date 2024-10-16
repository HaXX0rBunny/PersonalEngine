#include "MainMenuEditor.h"


std::string MainMenuEditor::currentfile = "None.json";
bool showInvalidFileDialog = false;
bool showObjectEditDialog = false;
bool showObjectDialog = false;
bool showComponentDialog = false;
bool showNewObjectPopup = false;
bool showRenamePopup = false;
bool showInvalidImageFileDialog = false;
bool unsavedChanges = true;
bool showUnsavedChangesPopup = false;
std::string selectedObjectName = "";
std::string openImagePath = "";
char texturePath[1000] = "";
char renameBuffer[1000] = "";
static char newObjectName[1000] = "";

void MainMenuEditor::TopBar()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		ImGui::Text("New File Menu");

		if (ImGui::MenuItem("New"))
		{
			if (unsavedChanges)
			{
				ShowSavePopup();  // �������� ���� �˾�
			}
			else
			{
				// �� ���� �۾� ���� (����� ���� ���� ��)
				currentfile = "None.json";
				GSM::GameStateManager::GetInstance()->Exit();
				GSM::GameStateManager::GetInstance()->Init();
			}
		}

		if (ImGui::MenuItem("Open", "Ctrl+O"))
		{
			GSM::GameStateManager::GetInstance()->Exit();
			GSM::GameStateManager::GetInstance()->Init();
			std::string openPath = WstrTostr(OpenFileDialog());
			if (unsavedChanges)
			{
				ShowSavePopup();
			}
			else
			{
				std::string openPath = WstrTostr(OpenFileDialog());
				if (!openPath.empty())
				{
					if (openPath.substr(openPath.find_last_of(".") + 1) == "json")
					{
						Serializer::Instance()->LoadLevel(openPath);
						currentfile = openPath;
						unsavedChanges = false;  // ������ ���� ��������� ���� ���·� ����
					}
					else
					{
						showInvalidFileDialog = true;
					}
				}
			}


		}

		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
			if (currentfile == "None.json")  
			{
				std::string savePath = WstrTostr(SaveFileDialog());
				if (!savePath.empty())
				{
					Serializer::Instance()->SaveLevel(savePath);
					currentfile = savePath;
					unsavedChanges = false;  
				}
			}
			else
			{
				Serializer::Instance()->SaveLevel(currentfile);
				unsavedChanges = false;  
			}
		}

		if (ImGui::MenuItem("Save As.."))
		{
			std::string savePath = WstrTostr(SaveFileDialog());
			if (!savePath.empty())
			{
				Serializer::Instance()->SaveLevel(savePath);
				currentfile = savePath;
				unsavedChanges = false;
			}
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::Text("New Game Object Menu");

		if (ImGui::MenuItem("New Object"))
		{
			showNewObjectPopup = true;  // Popup display �÷��� ����
		}

		if (ImGui::MenuItem("All Object", "Ctrl+I"))
		{
			showObjectDialog = true;  // Object List ǥ���ϱ� ���� �÷��� ����
		}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	if (showInvalidFileDialog)// Invalid File Dialog ó��
	{
		ImGui::OpenPopup("Invalid File Selected");
	}

	// �˾� â�� ����� Ȯ�� ��ư
	if (ImGui::BeginPopupModal("Invalid File Selected", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Unknown file type. Please select a .jsob file.");
		if (ImGui::Button("OK"))
		{
			ImGui::CloseCurrentPopup();
			showInvalidFileDialog = false;  // â�� ���� �� �÷��� ����
		}
		ImGui::EndPopup();
	}

	// New Object Popup 
	if (showNewObjectPopup)
	{
		ImGui::OpenPopup("Create New Object");  // Open Popup
		showNewObjectPopup = false;
	}

	if (ImGui::BeginPopupModal("Create New Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Enter Object Name:");

		ImGui::InputText("##ObjectName", newObjectName, IM_ARRAYSIZE(newObjectName));

		if (ImGui::Button("Create"))
		{
			if (strlen(newObjectName) > 0)
			{
				GameObject* newObj = new GameObject(newObjectName);
				strcpy_s(newObjectName, "");
				ImGui::CloseCurrentPopup();
			}
			else
			{
				ImGui::Text("Please enter a valid name.");
			}
		}

		ImGui::SameLine();


		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	if (showRenamePopup)
	{
		ImGui::OpenPopup("Rename Object");
		showRenamePopup = false;
	}


	if (ImGui::BeginPopupModal("Rename Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{

		ImGui::Text("Rename Object: %s", selectedObjectName.c_str());
		ImGui::InputText("New Name", renameBuffer, IM_ARRAYSIZE(renameBuffer));

		if (ImGui::Button("OK"))
		{

			if (strlen(renameBuffer) > 0)
			{
				auto obj = GameObjectManager::Instance();
				if (obj != nullptr)
				{
					obj->RenameKey(selectedObjectName, renameBuffer);
					selectedObjectName = renameBuffer;
				}
				strcpy_s(renameBuffer, "");
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	// Object list Window
	if (showObjectDialog)
	{
		ImGui::Begin("All Objects", &showObjectDialog, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("All objects, Click or Right-Click to Edit");

		for (const auto& obj : GameObjectManager::Instance()->AllObj())
		{
			if (ImGui::Selectable(obj.first.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 20)))
			{
				selectedObjectName = obj.first;
				showObjectEditDialog = true;     // Obeject Edit window state ����
			}

			// ��Ŭ�� �� �˾� �޴� ����
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImGui::OpenPopup(("##RightClickPopup_" + obj.first).c_str());
			}


			if (ImGui::BeginPopup(("##RightClickPopup_" + obj.first).c_str()))
			{
				if (ImGui::MenuItem("Rename"))
				{

					strcpy_s(renameBuffer, sizeof(renameBuffer), obj.first.c_str());
					selectedObjectName = obj.first;
					showRenamePopup = true;
				}

				if (ImGui::MenuItem("Delete"))
				{
					GameObjectManager::Instance()->RemoveObj(obj.first);
				}

				ImGui::EndPopup();
			}

		}
		ImGui::Separator();


		if (ImGui::Button("New Object"))
		{
			showNewObjectPopup = true;
		}
		ImGui::End();
	}

	if (showObjectEditDialog)
	{
		ImGui::Begin("Object Components", &showObjectEditDialog, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Editing Object: %s", selectedObjectName.c_str());


		if (GameObjectManager::Instance()->GetObj(selectedObjectName) != nullptr)
		{
			auto object = GameObjectManager::Instance()->GetObj(selectedObjectName);
			ImGui::Text("Components:");

			for (const auto& component : object->AllComponent())
			{
				if (ImGui::TreeNode(component.first.c_str()))
				{
					// SpriteComponent ����
					if (component.first == "SpriteComp") {
						if (const auto& spriteComp = object->GetComponent<SpriteComp>())
						{
							ImGui::Text("Sprite Component");

							// Color, Alpha, Texture Path UI
							glm::vec3& color = spriteComp->Getcolor();
							if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
							{
								spriteComp->SetColor(color.r, color.g, color.b);
							}

							float alpha = spriteComp->GetAlpha();
							if (ImGui::SliderFloat("Alpha", &alpha, 0.0f, 1.0f))
							{
								spriteComp->SetAlpha(alpha);
							}

							// �ؽ�ó ��� ���� (Assets ���� ������ ��θ� ǥ��)
							size_t pos_ = spriteComp->GetPath().find("Assets/");
							if (pos_ != std::string::npos)  // ��ο��� "Assets/"�� ã�� ��쿡�� ó��
							{
								const std::string& path_ = spriteComp->GetPath().substr(pos_ + std::string("Assets/").length());
								strcpy_s(texturePath, sizeof(texturePath), path_.c_str());

								//std::cout << "hey..." << std::endl;
							}
							else
							{
								// ��ΰ� ��ȿ���� ���� ��� �� ���ڿ��� �����ϰų� �⺻�� ó��
								strcpy_s(texturePath, sizeof(texturePath), spriteComp->GetPath().c_str());

							}

							if (ImGui::Button("Find.."))
							{
								openImagePath = WstrTostr(OpenImageFileDialog());
								if (!openImagePath.empty())
								{
									// 'Assets\' ��� ������ ���� ��θ� ���
									size_t pos = openImagePath.find("Assets\\");
									if (pos != std::string::npos) // ��ο��� "Assets\\"�� ã�� ��쿡�� ó��
									{
										openImagePath = openImagePath.substr(pos + std::string("Assets\\").length());
									}

									// Ȯ���� �˻� (png, jpg)
									std::string extension = openImagePath.substr(openImagePath.find_last_of(".") + 1);
									if (extension == "png" || extension == "jpg")
									{
										// ��ȿ�� �̹����� ��� �ؽ�ó ��� ����
										strcpy_s(texturePath, sizeof(texturePath), openImagePath.c_str());
										spriteComp->SetTexture(std::string(texturePath));
										std::cout << "SetTexture called..." << std::endl;
									}
									else
									{
										// ��ȿ���� ���� �̹��� ������ ��� ��� �˾� ǥ��
										showInvalidImageFileDialog = true;
									}
								}
							}

							// �̹��� ���� ��� �˾�
							if (showInvalidImageFileDialog)
							{
								ImGui::OpenPopup("Invalid Image File");
								showInvalidImageFileDialog = false;
							}

							if (ImGui::BeginPopupModal("Invalid Image File", NULL, ImGuiWindowFlags_AlwaysAutoResize))
							{
								ImGui::Text("Please select a valid image file (.png or .jpg).");
								if (ImGui::Button("OK"))
								{
									ImGui::CloseCurrentPopup();
								}
								ImGui::EndPopup();
							}

							ImGui::SameLine();
							ImGui::Text("%s", texturePath);
							/*   std::cout << texturePath << std::endl;
							   if (ImGui::InputText("Press Enter", texturePath, IM_ARRAYSIZE(texturePath)))
							   {
								   if (ImGui::IsKeyPressed(ImGuiKey_Enter))
								   {
									   spriteComp->SetTexture(std::string(texturePath));
									   std::cout << "SetTexture called..." << std::endl;
								   }
							   }*/
						}
					}
					if (component.first == "TransformComp") {
						// TransformComponent ����
						if (const auto& transformComp = object->GetComponent<TransformComp>())
						{
							ImGui::Text("Transform Component");

							// Position, Scale, Rotation UI
							glm::vec3 Vpos = transformComp->GetPos();

							if (ImGui::DragFloat3("Position", glm::value_ptr(Vpos), 0.1f))
							{
								transformComp->SetPos(Vpos[0], Vpos[1], Vpos[2]);
							}
							glm::vec3 VScale = transformComp->GetScale();

							if (ImGui::DragFloat2("Scale", glm::value_ptr(VScale), 1.f))
							{
								transformComp->SetScale(VScale[0], VScale[1]);
							}

							float rot = transformComp->GetRot();
							if (ImGui::DragFloat("Rotation", &rot, 0.1f))
							{
								transformComp->SetRot(rot);
							}
						}
					}
					ImGui::TreePop();
				}
				// ��Ŭ�� �� �˾� �޴� ����
				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					ImGui::OpenPopup(("##RightClickPopup_" + component.first).c_str());
				}


				if (ImGui::BeginPopup(("##RightClickPopup_" + component.first).c_str()))
				{


					if (ImGui::MenuItem("Delete"))
					{
						object->RemoveComponent(component.second);
					}

					ImGui::EndPopup();
				}
			}

			ImGui::Separator();


			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("Add Component Popup");
			}
			if (ImGui::BeginPopup("Add Component Popup"))
			{
				// ���� ������Ʈ�� SpriteComponent�� �ִ��� Ȯ��
				if (object->GetComponent<SpriteComp>() == nullptr)
				{
					if (ImGui::MenuItem("Add Sprite Component"))
					{
						object->AddComponent<SpriteComp>();
					}
				}
				else
				{
					ImGui::MenuItem("Sprite Component (Already Added)", NULL, false, false);
				}

				// ���� ������Ʈ�� TransformComponent�� �ִ��� Ȯ��
				if (object->GetComponent<TransformComp>() == nullptr)
				{
					if (ImGui::MenuItem("Add Transform Component"))
					{
						object->AddComponent<TransformComp>();
					}
				}
				else
				{
					ImGui::MenuItem("Component (Already Added)", NULL, false, false);
				}

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}
}



void MainMenuEditor::FileMenu()
{
}

void MainMenuEditor::ShowSavePopup()
{
	if (unsavedChanges && !showUnsavedChangesPopup)  // ��������� �ְ�, �˾��� ������ �ʾ��� ����
	{
		ImGui::OpenPopup("Unsaved Changes");  // �˾� ���� �غ�
		showUnsavedChangesPopup = true;       // �˾��� �������� ǥ��
	}

	// �˾��� ������ ���� �� �κ��� �����
	if (ImGui::BeginPopupModal("Unsaved Changes", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("You have unsaved changes. Do you want to save?");
		if (ImGui::Button("Save"))
		{
			std::string savePath = WstrTostr(SaveFileDialog());
			if (!savePath.empty())
			{
				Serializer::Instance()->SaveLevel(savePath);
				currentfile = savePath;
				unsavedChanges = false;  // ���� �� ������� �������� ����
			}
			showUnsavedChangesPopup = false;  // �˾��� ������ ����
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Don't Save"))
		{
			unsavedChanges = false;  // �������� �ʰ� ������� �������� ����
			showUnsavedChangesPopup = false;  // �˾��� ������ ����
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			showUnsavedChangesPopup = false;  // �˾��� ������ ����
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}




