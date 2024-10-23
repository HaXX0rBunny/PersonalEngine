#pragma once

namespace GEM {
	class BaseEditor
	{
	public:
		virtual ~BaseEditor() = default;
		//Init
		virtual void Init() = 0;
		//Updat0
		virtual void Update() = 0;
		//Exit
		virtual void Exit() = 0;

	};

}