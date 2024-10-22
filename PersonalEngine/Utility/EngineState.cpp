#include "EngineState.h"
#include <iostream>
EngineMode EngineState::engineState_ = EngineMode::Editor;

void EngineState::UpdateEnigneState()
{
	static bool prevKeystateF5 = GL_FALSE;
    if (Keystate::keystateF5 == GL_TRUE && prevKeystateF5 == GL_FALSE)
    {
        // ���� ��ȯ
        if (EngineState::engineState_ == EngineMode::Editor)
        {
            EngineState::engineState_ = EngineMode::Play;
        }
        else if (EngineState::engineState_ == EngineMode::Play)
        {
            EngineState::engineState_ = EngineMode::Editor;
        }

    }

    // ���� F5 Ű ���¸� ����
    prevKeystateF5 = Keystate::keystateF5;
	
}
