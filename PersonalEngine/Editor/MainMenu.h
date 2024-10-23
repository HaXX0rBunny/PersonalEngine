#pragma once
#include <string>
#include "../GameEditorManager/BaseEditor.h"
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
#include "../Component/CollisionComponent.h"
#include "../Utility/Filedialog.h"
#include "../Utility/CompareFile.h"
#include "../Utility/EngineState.h"
#include <unordered_map>
enum SaveState {
    Save,
    Cancel,
    nSave,
    None
};

class MainMenu {
private:
    std::string currentfile;
    char buffer[100];
    SaveState saveState;
    bool showInvalidFileDialog;
    bool showObjectEditDialog;
    bool showObjectDialog;
    bool showComponentDialog;
    bool showNewObjectPopup;
    bool showRenamePopup;
    bool unsaved;
    bool showInvalidImageFileDialog;
    bool isEditor;
    SaveState savedChangesState;
    std::string selectedObjectName;
    std::string openImagePath;
    std::string pendingOpenPath;
    char texturePath[1000];
    char renameBuffer[1000];
    char newObjectName[1000];
    std::unordered_map<std::string, std::function<void(GameObject*, BaseComponent*)>> componentUIHandlers;
public:
    // 기본 생성자에서 초기화
    MainMenu();
    void Update();
    // 함수 선언
    void TopBar();

    void PopupMenu();
    void ShowSavePopup();

    void InvalidFileDialog();
    void StartNewFile();
    void OpenNewFile(const std::string& openPath);

    void ShowObjectDialog();
    void NewObjectPopup();
    void RenamePopup();

    
    void ShowObjectEditDiaglog();

    void ShowAddComponentMenu(GameObject* object);


    void InvalidImageFileDialog();


    void InitializeComponentUIHandlers();

    void UpdateEditorState();

    template<typename T>
    void AddComponentIfNotExist(GameObject* object, const char* componentName);

};
