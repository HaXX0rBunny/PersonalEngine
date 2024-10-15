#include "MainMenuEditor.h"
#include "../Utility/Filedialog.h"

std::string MainMenuEditor::currentfile = "None";
bool showInvalidFileDialog = false;
bool showObjectEditDialog = false;
bool showObjectDialog = false;
bool showComponentDialog = false;
bool showNewObjectPopup = false;
bool showRenamePopup = false;
std::string selectedObjectName= "";
char renameBuffer[128] = ""; 
static char newObjectName[128] = "";

void MainMenuEditor::TopBar()
{
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
        ImGui::Text("New File Menu");

        if (ImGui::MenuItem("New"))
        {
            currentfile = "None.json";
            GSM::GameStateManager::GetInstance()->Exit();
            GSM::GameStateManager::GetInstance()->Init();
        }

        if (ImGui::MenuItem("Open", "Ctrl+O"))
        {
            GSM::GameStateManager::GetInstance()->Exit();
            GSM::GameStateManager::GetInstance()->Init();
            std::string openPath = WstrTostr(OpenFileDialog());
            if (!openPath.empty())
            {
                if (openPath.substr(openPath.find_last_of(".") + 1) == "json")
                {
                    Serializer::Instance()->LoadLevel(openPath);
                    currentfile = openPath;
                }
                else
                {
                    showInvalidFileDialog = true;
                }
            }
        }

        if (ImGui::MenuItem("Save", "Ctrl+S"))
        {
            Serializer::Instance()->SaveLevel(currentfile);
        }

        if (ImGui::MenuItem("Save As.."))
        {
            std::string savePath = WstrTostr(SaveFileDialog());
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

    ImGui::EndMainMenuBar();

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
                auto obj=GameObjectManager::Instance();
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
                            float* fcolor[3]{ &color.r, &color.g, &color.b };
                            if (ImGui::ColorEdit3("Color", *fcolor))
                            {
                                spriteComp->SetColor(color[0], color[1], color[2]);
                            }

                            float alpha = spriteComp->GetAlpha();
                            if (ImGui::SliderFloat("Alpha", &alpha, 0.0f, 1.0f))
                            {
                                spriteComp->SetAlpha(alpha);
                            }

                            char texturePath[256] = "";
                            strcpy_s(texturePath, sizeof(texturePath), spriteComp->GetPath().c_str());
                            if (ImGui::InputText("Texture Path", texturePath, IM_ARRAYSIZE(texturePath)))
                            {
                                spriteComp->SetTexture(std::string(texturePath));
                            }
                        }
                    } 
                    if (component.first == "TransformComp") {
                        // TransformComponent 조절
                        if (const auto& transformComp = object->GetComponent<TransformComp>())
                        {
                            ImGui::Text("Transform Component");

                            // Position, Scale, Rotation UI
                            glm::vec3 Vpos = transformComp->GetPos();
                            float pos[3] = { Vpos.x,Vpos.y,Vpos.z };
                            if (ImGui::DragFloat3("Position", pos, 0.1f))
                            {
                                transformComp->SetPos(pos[0], pos[1], pos[2]);
                            }
                            glm::vec3 VScale = transformComp->GetScale();
                            float scale[2] = { VScale.x, VScale.y };
                            if (ImGui::DragFloat2("Scale", scale, 1.f))
                            {
                                transformComp->SetScale(scale[0], scale[1]);
                            }

                            float rot[1] = { transformComp->GetRot() };
                            if (ImGui::DragFloat("Rotation", rot, 0.1f))
                            {
                                transformComp->SetRot(rot[0]);
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



void MainMenuEditor::FileMenu()
{
}
