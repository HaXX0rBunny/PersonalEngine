#pragma once
class TileEditor
{

	bool isEnabled;
	TileEditor(const TileEditor& other) = delete;
	const TileEditor& operator=(const TileEditor& other) = delete;
	~TileEditor();
	TileEditor() :isEnabled(false) {
	
	
	};

public:

	static TileEditor* GetInstance() {
		static TileEditor Instance;  // ½Ì±ÛÅæ ÆÐÅÏ »ç¿ë
		return &Instance;
	}
	void Update();

	void Clear();

};