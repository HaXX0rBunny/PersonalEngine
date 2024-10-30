#include "EditorInteractManager.h"

EditorInteractManager EditorInteractManager::Instance;

EditorInteractManager::EditorInteractManager() : selectedObject(nullptr), lastMousePos({0,0})
, isDragging(false), currentMode(EditMode::Position) {}
glm::vec2 EditorInteractManager::ScreenToWorldPosition(const glm::vec2& screenPos)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glm::mat4 viewProj = Camera::GetInstance()->GetViewMatrix();
    glm::mat4 projection = Camera::GetInstance()->GetProjectionMatrix();
    glm::mat4 viewProjMatrix = projection * viewProj;
    glm::vec4 screenPosNDC(
        (2.0f * screenPos.x) / viewport[2] - 1.0f,
        1.0f - (2.0f * screenPos.y) / viewport[3],
        -1.0f,
        1.0f
    );

 glm::vec4 worldPos = glm::inverse(viewProjMatrix) * screenPosNDC;
    return glm::vec2(worldPos.x / worldPos.w, worldPos.y / worldPos.w);
}
bool EditorInteractManager::IsPointInBounds(const glm::vec2& point, GameObject* object)
{
    if (!object) return false;

    auto transform = object->GetComponent<TransformComp>();
    if (!transform) return false;

    glm::vec3 pos = transform->GetPos();
    glm::vec3 scale = transform->GetScale();
    float rotation = transform->GetRot();

    // ���� ��ǥ��� ��ȯ
    glm::vec2 localPoint(point.x - pos.x, point.y - pos.y);

    // ȸ�� ����ȯ ����
    float cosTheta = cos(-rotation);
    float sinTheta = sin(-rotation);
    glm::vec2 rotatedPoint(
        localPoint.x * cosTheta - localPoint.y * sinTheta,
        localPoint.x * sinTheta + localPoint.y * cosTheta
    );

    return (abs(rotatedPoint.x) <= scale.x / 2.0f &&
        abs(rotatedPoint.y) <= scale.y / 2.0f);
}
void EditorInteractManager::Update()
{

    if (Keystate::keystateQ==GL_TRUE) 
        currentMode = EditMode::Position;
    if (Keystate::keystateW == GL_TRUE)
        currentMode = EditMode::Rotation;
    if (Keystate::keystateE == GL_TRUE)
        currentMode = EditMode::Scale;

    // ���� ���콺 ��ư Ŭ�� Ȯ��
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        double MouseX, MouseY;
        glfwGetCursorPos(glfwGetCurrentContext(), &MouseX, &MouseY);
        //ImVec2 mousePos = ImGui::GetMousePos();
        CheckMouseToCollision(glm::vec2(MouseX, MouseY));
    }

    // �巡�� ó��
    if (selectedObject && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImVec2 mousePos = ImGui::GetMousePos();
        glm::vec2 currentMousePos = ScreenToWorldPosition(glm::vec2(mousePos.x, mousePos.y));

        if (!isDragging) {
            StartDragging(currentMousePos);
        }
        else {
            glm::vec2 delta = currentMousePos - lastMousePos;

            if (auto transform = selectedObject->GetComponent<TransformComp>()) {
                switch (currentMode) {
                case EditMode::Position:
                {
                    const float positionSpeed = 0.5f;
                    glm::vec3 position = transform->GetPos();
                    position.x += delta.x * positionSpeed;
                    position.y += delta.y * positionSpeed;
                    transform->SetPos(position);
                }
                break;

                case EditMode::Rotation:
                {
                    const float rotationSpeed = 0.1f;
                    float rotation = transform->GetRot();
                    rotation += delta.x * rotationSpeed;
                    transform->SetRot(rotation);
                }
                break;

                case EditMode::Scale:
                {
                    const float scaleSpeed = 0.01f;
                    glm::vec3 scale = transform->GetScale();
                    scale.x += delta.x * scaleSpeed;
                    scale.y += delta.y * scaleSpeed;
                    // �ּ� ������ ����
                    scale = glm::max(scale, glm::vec3(0.1f));
                    transform->SetScale(scale);
                }
                break;
                }
            }
            lastMousePos = currentMousePos;
        }
    }

    // ���콺 ��ư�� ������ ��
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        EndDragging();
    }

    // ���õ� ������Ʈ �Ӽ� ǥ��
    if (selectedObject) {
        ShowObjectProperties();
    }
}

// �Ӽ� â ǥ�ø� ���� ������ �Լ�
void EditorInteractManager::ShowObjectProperties()
{
    std::cout << selectedObject << std::endl;
    ImGui::Begin("Object Properties");
    ImGui::Text("Selected Object: %s", selectedObject->GetName().c_str());

    // ���� ��� ���� UI
    const char* modes[] = { "Position", "Rotation", "Scale" };
    int currentModeIndex = static_cast<int>(currentMode);
    if (ImGui::Combo("Edit Mode", &currentModeIndex, modes, IM_ARRAYSIZE(modes))) {
        currentMode = static_cast<EditMode>(currentModeIndex);
    }

    if (!selectedObject->GetComponent<TransformComp>())
    {

        ImGui::End();
        return;
    }
    if (auto transform = selectedObject->GetComponent<TransformComp>()) {
        glm::vec3 position = transform->GetPos();
        if (ImGui::DragFloat3("Position", &position[0], 0.1f)) {
            transform->SetPos(position);
        }

        glm::vec3 scale = transform->GetScale();
        if (ImGui::DragFloat3("Scale", &scale[0], 0.1f)) {
            transform->SetScale(scale);
        }

        float rotation = transform->GetRot();
        if (ImGui::DragFloat("Rotation", &rotation, 1.0f)) {
            transform->SetRot(rotation);
        }
    }

    ImGui::End();
}
void EditorInteractManager::CheckMouseToCollision(const glm::vec2& CVmousePos_in) {
    if (ImGui::IsAnyItemHovered()) {
        selectedObject = nullptr;
        return;
    }

    // ��ũ�� ��ǥ�� ���� ��ǥ�� ��ȯ
    glm::vec2 worldPos = ScreenToWorldPosition(CVmousePos_in);

    const auto& objects = GameObjectManager::Instance()->AllObj();
    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
        // IsPointInBounds �Լ��� ����Ͽ� ȸ���� ����� �浹 �˻�
        if (IsPointInBounds(worldPos, it->second)) {
            selectedObject = it->second;
            return;
        }
    }

    selectedObject = nullptr;
}

void EditorInteractManager::StartDragging(const glm::vec2& startPos)
{
	isDragging = true;
	lastMousePos = startPos;
}