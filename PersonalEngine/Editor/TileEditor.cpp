#include "TileEditor.h"
#include "../Utility/InputProcess.h"
TileEditor::~TileEditor()
{
}

void TileEditor::Update()
{
    // F1 Ű�� ���
    if (Keystate::keystateF1 == GL_TRUE) {
        isEnabled = !isEnabled;
        if (!isEnabled) {
            Clear();
        }
        Keystate::keystateF1 = GL_FALSE;
    }

    if (!isEnabled) return;

    /*�׸��� ���� */
}

void TileEditor::Clear()
{
}
