#include "EngineState.h"
#include <iostream>
EngineMode EngineState::engineState_ = EngineMode::Editor;

void EngineState::UpdateEnigneState()
{

	if (Keystate::keystateF5)
	{
		if (EngineState::engineState_ == EngineMode::Editor)
			EngineState::engineState_ = EngineMode::Play;
		else
			EngineState::engineState_ = EngineMode::Editor;
	}
	
}
