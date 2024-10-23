#pragma once

class EditorInteractManager
{
public:
	static EditorInteractManager* GetInstance()
	{
		static EditorInteractManager Instance;
		return &Instance;
	};
	void update();

};