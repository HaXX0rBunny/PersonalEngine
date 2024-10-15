#include "MainMenuEditor.h"
#include "../Utility/Filedialog.h"

std::string MainMenuEditor::currentfile = "None";
bool showInvalidFileDialog = false;
bool showObjectEditDialog = false;
bool showObjectDialog = false;
bool showComponentDialog = false;
bool showNewObjectPopup = false;
bool showRenamePopup = false;
std::string selectedObjectName;
char renameBuffer[128] = "";  // 리네임할 때 사용할 버퍼
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
            showNewObjectPopup = true;  // 팝업을 띄우기 위한 플래그 설정
        }

        if (ImGui::MenuItem("All Object", "Ctrl+I"))
        {
            showObjectDialog = true;  // 오브젝트 리스트 창을 표시하기 위한 플래그 설정
        }

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    // 새 오브젝트 생성 팝업 처리
    if (showNewObjectPopup)
    {
        ImGui::OpenPopup("Create New Object");  // 팝업 열기
        showNewObjectPopup = false;  // 플래그 리셋
    }

    if (ImGui::BeginPopupModal("Create New Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Enter Object Name:");

        ImGui::InputText("##ObjectName", newObjectName, IM_ARRAYSIZE(newObjectName));

        if (ImGui::Button("Create"))
        {
            if (strlen(newObjectName) > 0)  // 이름이 비어있지 않으면 오브젝트 생성
            {
                GameObject* newObj = new GameObject(newObjectName);
                strcpy_s(newObjectName, "");  // 입력 버퍼 초기화
                ImGui::CloseCurrentPopup();   // 팝업 닫기
            }
            else
            {
                ImGui::Text("Please enter a valid name.");
            }
        }

        ImGui::SameLine();

        // 취소 버튼
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    if (showRenamePopup)
    {
        ImGui::OpenPopup("Rename Object");  // 팝업 열기
        showRenamePopup = false;  // 플래그 리셋
    }

    // 리네임 팝업 처리
    if (ImGui::BeginPopupModal("Rename Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Rename Object: %s", selectedObjectName.c_str());
        ImGui::InputText("New Name", renameBuffer, IM_ARRAYSIZE(renameBuffer));

        if (ImGui::Button("OK"))
        {
            // 이름이 유효한지 확인하고 리네임 적용
            if (strlen(renameBuffer) > 0)
            {
                auto obj = GameObjectManager::Instance()->GetObj(selectedObjectName);
                if (obj != nullptr)
                {
                    obj->Renamed(renameBuffer);  // 리네임 적용
                    selectedObjectName = renameBuffer;  // 선택된 이름 갱신
                }
                strcpy_s(renameBuffer, "");  // 리네임 버퍼 초기화
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
    // 오브젝트 리스트 창
    if (showObjectDialog)
    {
        ImGui::Begin("All Objects", &showObjectDialog, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("All objects, Click or Right-Click to Edit");

        for (const auto& obj : GameObjectManager::Instance()->AllObj())
        {
            if (ImGui::Selectable(obj.first.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 20)))  // 크기를 약간 크게 설정하여 버튼 느낌 추가
            {
                selectedObjectName = obj.first;  // 선택된 오브젝트 이름 저장
                showObjectEditDialog = true;     // 오브젝트 편집 창을 열도록 설정
            }

            // 우클릭 시 팝업 메뉴 열기
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup(("##RightClickPopup_" + obj.first).c_str());
            }

            // 우클릭 팝업 메뉴
            if (ImGui::BeginPopup(("##RightClickPopup_" + obj.first).c_str()))
            {
                if (ImGui::MenuItem("Rename"))
                {
                    // 리네임을 위한 버퍼에 현재 이름 복사
                    strcpy_s(renameBuffer, sizeof(renameBuffer), obj.first.c_str());
                    showNewObjectPopup = true;  // 리네임 팝업 열기
                }

                if (ImGui::MenuItem("Delete"))
                {
                    GameObjectManager::Instance()->RemoveObj(obj.first);
                }

                ImGui::EndPopup();
            }

        }
        ImGui::Separator();

        // 컴포넌트 추가 버튼 및 UI
        if (ImGui::Button("New Object"))
        {
            showNewObjectPopup = true;
        }
        ImGui::End();  // 오브젝트 리스트 창 끝내기
    }

    // 선택된 오브젝트의 컴포넌트와 추가 기능을 같은 창에 표시
    if (showObjectEditDialog)
    {
        ImGui::Begin("Object Components", &showObjectEditDialog, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Editing Object: %s", selectedObjectName.c_str());

        // 선택된 오브젝트의 컴포넌트를 표시
        if (GameObjectManager::Instance()->GetObj(selectedObjectName) != nullptr)
        {
            auto object = GameObjectManager::Instance()->GetObj(selectedObjectName);
            ImGui::Text("Components:");

            for (const auto& component : object->AllComponent())
            {
                if (ImGui::Selectable(component.first.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 20)))  // 크기를 약간 크게 설정하여 버튼 느낌 추가
                {
                    selectedObjectName = component.first;  // 선택된 오브젝트 이름 저장
                    showComponentDialog = true;    
                }

                // 우클릭 시 팝업 메뉴 열기
                if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    ImGui::OpenPopup(("##RightClickPopup_" + component.first).c_str());
                }

                // 우클릭 팝업 메뉴
                if (ImGui::BeginPopup(("##RightClickPopup_" + component.first).c_str()))
                {
                    if (ImGui::MenuItem("Select"))
                    {
                        // 리네임을 위한 버퍼에 현재 이름 복사
                        selectedObjectName = component.first;  // 선택된 오브젝트 이름 저장
                        showComponentDialog = true;
                    }

                    if (ImGui::MenuItem("Delete"))
                    {
                        object->RemoveComponent(component.first);
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::Separator();

            // 컴포넌트 추가 버튼 및 UI
            if (ImGui::Button("Add Component"))
            {
                // 컴포넌트 추가 기능 (예시로 구현 가능)
            }
        }
    
        ImGui::End();
    }
}


void MainMenuEditor::FileMenu()
{
}
