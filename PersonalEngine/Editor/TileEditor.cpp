#include "TileEditor.h"
#include "../Utility/InputProcess.h"
#include "../GameEditorManager/EditorInteractManager.h"
void TileEditor::Update()
{
    // F2 키로 토글
    if (Keystate::keystateF2 == GL_TRUE) {
        isEnabled = !isEnabled;
        Keystate::keystateF2 = GL_FALSE;
    }
    if (!isEnabled) return;
    DrawGrid();
    ShowTileMenu();

    // 마우스 위치 가져오기
    ImVec2 mousePos = ImGui::GetMousePos();
    glm::vec2 worldPos = EditorInteractManager::GetInstance()->ScreenToWorldPosition(
        glm::vec2(mousePos.x, mousePos.y));
    glm::vec2 snappedPos = SnapToGrid(worldPos);

    // 마우스 클릭 처리
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered()) {
        isDragging = true;
        dragStart = snappedPos;
        CreateTileObject(snappedPos);
    }

    // 드래그 처리
    if (isDragging && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        glm::vec2 currentTilePos = snappedPos;
        if (currentTilePos != lastTilePos) {
            CreateTileObject(currentTilePos);
            lastTilePos = currentTilePos;
        }
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        isDragging = false;
        lastTilePos = glm::vec2(-1);
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
        auto objects = GameObjectManager::Instance()->AllObj();
        for (const auto& obj : objects) {
            auto transform = obj.second->GetComponent<TransformComp>();
            if (transform) {
                glm::vec2 objPos(transform->GetPos().x, transform->GetPos().y);
                // 현재 마우스 위치의 타일과 오브젝트 위치가 일치하는지 확인
                if (glm::distance(objPos, snappedPos) < TILE_SIZE / 2) {
                    GameObjectManager::Instance()->RemoveObj(obj.first);
                    break;
                }
            }
        }
    }
}

void TileEditor::DrawGrid()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    // 화면 크기
    float windowWidth = 1580.0f;   // Window_width
    float windowHeight = 780.0f;   // Window_height

    // 세로선 그리기
    for (float x = -20.f; x <= windowWidth; x += TILE_SIZE) {
        drawList->AddLine(
            ImVec2(x, 0),
            ImVec2(x, windowHeight),
            ImGui::ColorConvertFloat4ToU32(GRID_COLOR)
        );
    }

    // 가로선 그리기
    for (float y = -20.f; y <= windowHeight; y += TILE_SIZE) {
        drawList->AddLine(
            ImVec2(0, y),
            ImVec2(windowWidth, y),
            ImGui::ColorConvertFloat4ToU32(GRID_COLOR)
        );
    }
}

void TileEditor::CreateTileObject(const glm::vec2& position)
{
    static int objectCounter = 0;
    std::string objName = "Tile_" + std::to_string(objectCounter++);

    GameObject* newObject = new GameObject(objName);
    TransformComp* transform =newObject->AddComponent<TransformComp>();
    transform->SetPos(position.x, position.y, 0);
    transform->SetScale(TILE_SIZE, TILE_SIZE);
    SpriteComp* Sprite = newObject->AddComponent<SpriteComp>();
    CollisionComp* Collision =  newObject->AddComponent<CollisionComp>();
    switch (currentTileType) {
    case TileType::Wall:
        newObject->ObjectTag = GameObject::Tag::Wall;
        Sprite->SetTexture("Assets/wall.png");
        break;

    case TileType::Block:
        newObject->ObjectTag = GameObject::Tag::Block;
        newObject->AddComponent<BlockComp>();
        Sprite->SetTexture("Assets/block.png");
        break;

    case TileType::Player:
        newObject->ObjectTag = GameObject::Tag::Player;
        newObject->AddComponent<PlayerComp>();
        newObject->AddComponent<RigidbodyComp>();
        Sprite->SetTexture("Assets/player.png");
        break;
    }

}

glm::vec2 TileEditor::SnapToGrid(const glm::vec2& position)
{
    return glm::vec2(
        std::round(position.x / TILE_SIZE) * TILE_SIZE,
        std::round(position.y / TILE_SIZE) * TILE_SIZE
    );
}

void TileEditor::ShowTileMenu()
{
    ImGui::Begin("Tile Menu");
    if (ImGui::RadioButton("Wall", currentTileType == TileType::Wall))
        currentTileType = TileType::Wall;
    if (ImGui::RadioButton("Brock", currentTileType == TileType::Block))
        currentTileType = TileType::Block;
    if (ImGui::RadioButton("Player", currentTileType == TileType::Player))
        currentTileType = TileType::Player;
    ImGui::End();
}
