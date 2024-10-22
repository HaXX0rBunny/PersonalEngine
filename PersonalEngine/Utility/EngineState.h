#pragma once
#include "InputProcess.h"
#include "../Serializer/Serializer.h"
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
