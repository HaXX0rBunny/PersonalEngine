#include "TileEditor.h"
#include "../Utility/InputProcess.h"
void TileEditor::Update()
{
    // F2 Ű�� ���
    if (Keystate::keystateF2 == GL_TRUE) {
        isEnabled = !isEnabled;
        Keystate::keystateF2 = GL_FALSE;
    }

    if (isEnabled) {
        DrawGrid();
    }
}

void TileEditor::DrawGrid()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    // ȭ�� ũ��
    float windowWidth = 1600.0f;   // Window_width
    float windowHeight = 800.0f;   // Window_height

    // ���μ� �׸���
    for (float x = 0; x <= windowWidth; x += TILE_SIZE) {
        drawList->AddLine(
            ImVec2(x, 0),
            ImVec2(x, windowHeight),
            ImGui::ColorConvertFloat4ToU32(GRID_COLOR)
        );
    }

    // ���μ� �׸���
    for (float y = 0; y <= windowHeight; y += TILE_SIZE) {
        drawList->AddLine(
            ImVec2(0, y),
            ImVec2(windowWidth, y),
            ImGui::ColorConvertFloat4ToU32(GRID_COLOR)
        );
    }
}