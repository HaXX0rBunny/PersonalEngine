#pragma once
#include "InputProcess.h"
enum EngineMode
{
	Play,
	Editor
};


struct EngineState
{
	static EngineMode engineState_;
	static void UpdateEnigneState();
};
