#include "EditorInteractManager.h"

void EditorInteractManager::Update()
{
	if (Keystate::keystateLBtn)
	{
		glm::vec2 mousePos = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
		CheckMouseToCollision(mousePos);
	
	}
}

void EditorInteractManager::CheckObject()
{
}

void EditorInteractManager::CheckMouseToCollision(const glm::vec2& CVmousePos_in)
{

}
