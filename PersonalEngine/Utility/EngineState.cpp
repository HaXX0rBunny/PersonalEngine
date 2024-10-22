#include "EngineState.h"
#include <iostream>
EngineMode EngineState::engineState_ = EngineMode::Editor;

void EngineState::UpdateEnigneState()
{
	static bool prevKeystateF5 = GL_FALSE;
    if (Keystate::keystateF5 == GL_TRUE && prevKeystateF5 == GL_FALSE)
    {
        // 상태 전환
        if (EngineState::engineState_ == EngineMode::Editor)
        {
            EngineState::engineState_ = EngineMode::Play;
        }
        else if (EngineState::engineState_ == EngineMode::Play)
        {
            EngineState::engineState_ = EngineMode::Editor;
        }

    }

    // 현재 F5 키 상태를 저장
    prevKeystateF5 = Keystate::keystateF5;
	
}
