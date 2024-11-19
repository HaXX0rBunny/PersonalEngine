#include "TileEditor.h"
#include "../Utility/InputProcess.h"
TileEditor::~TileEditor()
{
}

void TileEditor::Update()
{
    // F1 키로 토글
    if (Keystate::keystateF1 == GL_TRUE) {
        isEnabled = !isEnabled;
        if (!isEnabled) {
            Clear();
        }
        Keystate::keystateF1 = GL_FALSE;
    }

    if (!isEnabled) return;

    /*그리드 격자 */
}

void TileEditor::Clear()
{
}
