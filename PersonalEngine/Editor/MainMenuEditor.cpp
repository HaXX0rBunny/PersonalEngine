#include "MainMenuEditor.h"


std::string MainMenuEditor::currentfile = "None.json";
bool showInvalidFileDialog = false;
bool showObjectEditDialog = false;
bool showObjectDialog = false;
bool showComponentDialog = false;
bool showNewObjectPopup = false;
bool showRenamePopup = false;
bool unsaved = false;
bool showInvalidImageFileDialog = false;
SaveState savedChangesState = None; // 초기 상태는 None으로 설정
std::string selectedObjectName = "";
std::string openImagePath = "";
std::string pendingOpenPath = "";  // 열릴 파일 경로 저장
char texturePath[1000] = "";
char renameBuffer[1000] = "";
char newObjectName[1000] = "";

void MainMenuEditor::TopBar()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		ImGui::Text("New File Menu");

		if (ImGui::MenuItem("New"))
		{
			if (unsaved)
			{
				savedChangesState = None;
				ShowSavePopup();  // 저장할지 묻는 팝업
			}
			unsaved = IsDataModified(currentfile);
			
			if (savedChangesState != Cancel)
			{
				StartNewFile();
			}
			
		}

		if (ImGui::MenuItem("Open", "Ctrl+O"))
		{
			unsaved = IsDataModified(currentfile);
			
			if (unsaved)
			{
				// 저장할지 물어보는 팝업을 띄우고, 열려는 파일 경로를 미리 저장

				pendingOpenPath = WstrTostr(OpenFileDialog());
				savedChangesState = None;
				ShowSavePopup();
			}
			else
			{
				// 변경사항이 없다면 바로 파일 열기
				OpenNewFile(WstrTostr(OpenFileDialog()));
			}
		}

		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
			if (currentfile == "None.json")
			{
				std::string savePath = WstrTostr(SaveFileDialog(currentfile));
				if (!savePath.empty())
				{
					Serializer::Instance()->SaveLevel(savePath);
					currentfile = savePath;
				}
			}
			else
			{
				Serializer::Instance()->SaveLevel(currentfile);

			}
		}

		if (ImGui::MenuItem("Save As.."))
		{
			std::string savePath = WstrTostr(SaveFileDialog(currentfile));
			if (!savePath.empty())
			{
				Serializer::Instance()->SaveLevel(savePath);
				currentfile = savePath;

			}
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::Text("New Game Object Menu");

		if (ImGui::MenuItem("New Object"))
		{
			showNewObjectPopup = true;  // Popup display 플래그 설정
		}

		if (ImGui::MenuItem("All Object", "Ctrl+I"))
		{
			showObjectDialog = true;  // Object List 표시하기 위한 플래그 설정
		}

		ImGui::EndMenu();
	}
	PopupMenu();

	ImGui::EndMainMenuBar();
	

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
				showObjectEditDialog = true;     // Obeject Edit window state 설정
			}

			// 우클릭 시 팝업 메뉴 열기
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
					// SpriteComponent 조절
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

							// 텍스처 경로 설정 (Assets 폴더 이후의 경로만 표시)
							size_t pos_ = spriteComp->GetPath().find("Assets/");
							if (pos_ != std::string::npos)  // 경로에서 "Assets/"를 찾은 경우에만 처리
							{
								const std::string& path_ = spriteComp->GetPath().substr(pos_ + std::string("Assets/").length());
								strcpy_s(texturePath, sizeof(texturePath), path_.c_str());

								//std::cout << "hey..." << std::endl;
							}
							else
							{
								// 경로가 유효하지 않을 경우 빈 문자열을 설정하거나 기본값 처리
								strcpy_s(texturePath, sizeof(texturePath), spriteComp->GetPath().c_str());

							}

							if (ImGui::Button("Find.."))
							{
								openImagePath = WstrTostr(OpenImageFileDialog());
								if (!openImagePath.empty())
								{
									// 'Assets\' 경로 이후의 파일 경로를 사용
									size_t pos = openImagePath.find("Assets\\");
									if (pos != std::string::npos) // 경로에서 "Assets\\"를 찾은 경우에만 처리
									{
										openImagePath = openImagePath.substr(pos + std::string("Assets\\").length());
									}

									// 확장자 검사 (png, jpg)
									std::string extension = openImagePath.substr(openImagePath.find_last_of(".") + 1);
									if (extension == "png" || extension == "jpg")
									{
										// 유효한 이미지일 경우 텍스처 경로 설정
										strcpy_s(texturePath, sizeof(texturePath), openImagePath.c_str());
										spriteComp->SetTexture(std::string(texturePath));
										std::cout << "SetTexture called..." << std::endl;
									}
									else
									{
										// 유효하지 않은 이미지 파일일 경우 경고 팝업 표시
										showInvalidImageFileDialog = true;
									}
								}
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
						// TransformComponent 조절
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
				// 우클릭 시 팝업 메뉴 열기
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
				// 현재 오브젝트에 SpriteComponent가 있는지 확인
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

				// 현재 오브젝트에 TransformComponent가 있는지 확인
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



void MainMenuEditor::PopupMenu()
{
	ShowSavePopup();
	InvalidFileDialog();
	NewObjectPopup();
	RenamePopup();
}

void MainMenuEditor::ShowSavePopup()
{

	if (unsaved)  // 변경사항이 있을 때만 팝업을 띄우는 조건
	{
		ImGui::OpenPopup("Unsaved Changes");  // 팝업 열기 준비

	}
	// 팝업이 열렸을 때만 이 부분이 실행됨
	if (ImGui::BeginPopupModal("Unsaved Changes", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("You have unsaved changes. Do you want to save?");
		if (ImGui::Button("Save"))
		{
			std::string savePath = "";
			if (currentfile == "None.json")
				std::string savePath = WstrTostr(SaveFileDialog(currentfile));
			else
				savePath = currentfile;
			if (!savePath.empty())
			{
				Serializer::Instance()->SaveLevel(savePath);
				currentfile = savePath;
				savedChangesState = Save;
				unsaved = false;
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Don't Save"))
		{
			savedChangesState = nSave;
			ImGui::CloseCurrentPopup();
			unsaved = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			savedChangesState = Cancel;
			ImGui::CloseCurrentPopup();  // 작업을 중단하고 팝업을 닫음
			unsaved = false;

		}
		ImGui::EndPopup();  // 팝업을 닫는 함수

		if (savedChangesState == Save || savedChangesState == nSave)
		{
			if (!pendingOpenPath.empty())
			{
				OpenNewFile(pendingOpenPath);  // 파일 열기
				pendingOpenPath.clear();  // 경로 리셋
			}
		}
	}
}

void MainMenuEditor::InvalidFileDialog()
{
	
	if (showInvalidFileDialog)// Invalid File Dialog 처리
	{
		ImGui::OpenPopup("Invalid File Selected");
	}

	// 팝업 창의 내용과 확인 버튼
	if (ImGui::BeginPopupModal("Invalid File Selected", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Unknown file type. Please select a .jsob file.");
		if (ImGui::Button("OK"))
		{
			ImGui::CloseCurrentPopup();
			showInvalidFileDialog = false;  // 창을 닫은 후 플래그 리셋
		}
		ImGui::EndPopup();
	}
}

void MainMenuEditor::NewObjectPopup()
{
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
}

void MainMenuEditor::RenamePopup()
{

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
}

void MainMenuEditor::InvalidImageFileDialog()
{
	// 이미지 파일 경고 팝업
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
}

void MainMenuEditor::StartNewFile()
{
	// 새 파일 작업 시작 (저장된 내용 없을 때)

	currentfile = "None.json";
	GSM::GameStateManager::GetInstance()->Exit();
	GSM::GameStateManager::GetInstance()->Init();
}

void MainMenuEditor::OpenNewFile(const std::string& openPath)
{
	if (!openPath.empty() && openPath.substr(openPath.find_last_of(".") + 1) == "json")
	{
		GSM::GameStateManager::GetInstance()->Exit();
		GSM::GameStateManager::GetInstance()->Init();
		Serializer::Instance()->LoadLevel(openPath);
		currentfile = openPath;
		unsaved = false;  // 파일을 열면 변경사항이 없는 상태로 리셋
	}
	else if(openPath == ""){}
	else
	{
		showInvalidFileDialog = true;
	}
}


