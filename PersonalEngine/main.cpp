#define GLAD_GL_IMPLEMENTATION
#include <gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include "Setting_window.h"
#include <crtdbg.h> // To check for memory leaks
#include "GameObject/GameObject.h"
#include "GameObjectManager/GameObjectManager.h"
int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    setWindow_();
    GameObject* test = new GameObject("test");
   // test->AddComponent<BaseComponent>();
    auto it =GameObjectManager::Instance()->GetObj("test");
    it->Clear();
    return 0;
}

