#define GLAD_GL_IMPLEMENTATION
#include <gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Setting_window.h"
#include <crtdbg.h> // To check for memory leaks
#include "GameObject/GameObject.h"
#include "GameObjectManager/GameObjectManager.h"
int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    _CrtSetBreakAlloc(1461);
    SetWindow::setWindow_();

    return 0;

}

