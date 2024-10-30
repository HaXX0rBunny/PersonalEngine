#pragma once
#include <vector>

#include "../GameEditorManager/BaseEditor.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/TransformComponent.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Camera/Camera.h"
#include <glm.hpp>
#include "../Utility/InputProcess.h"


class EditorInteractManager {
private:
    enum class EditMode {
        Position,
        Rotation,
        Scale
    };

    static EditorInteractManager Instance;

    glm::vec2 lastMousePos;
    bool isDragging;
    EditMode currentMode;  // 현재 편집 모드



    EditorInteractManager();
    EditorInteractManager(const EditorInteractManager&) = delete;
    EditorInteractManager& operator=(const EditorInteractManager&) = delete;
    glm::vec2 ScreenToWorldPosition(const glm::vec2& screenPos);
    bool IsPointInBounds(const glm::vec2& point, GameObject* object);
public:
    GameObject* selectedObject;
    static EditorInteractManager* GetInstance() {
        return &Instance;
    }
    void SetEditMode(EditMode mode) { currentMode = mode; }
    void Update();

    void ShowObjectProperties();

    void CheckMouseToCollision(const glm::vec2& CVmousePos_in);

    // 피킹 관련 함수들
    GameObject* GetSelectedObject() const { return selectedObject; }
    void ClearSelection() { selectedObject = nullptr; }
    bool IsObjectSelected() const { return selectedObject != nullptr; }
    bool IsDragging() const { return isDragging; }
    // 드래깅 관련
    void StartDragging(const glm::vec2& startPos);
    void EndDragging() { isDragging = false; }
    

};