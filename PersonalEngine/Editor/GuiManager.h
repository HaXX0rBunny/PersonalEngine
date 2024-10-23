#pragma once
#include <map>
#include <iostream>
#include "MainMenuEditor.h"
class GuiManager
{
	std::map<MainMenuEditor*, std::string> UiConstainer;
	static GuiManager* Instance_;
public:
	GuiManager* Instance() {
		if (Instance_ == nullptr)
			Instance_ = new GuiManager();
		return Instance_;
	}

	void Update();
};