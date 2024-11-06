#include "InputProcess.h"
GLboolean Keystate::keystateW = GL_FALSE;
GLboolean Keystate::keystateS = GL_FALSE;
GLboolean Keystate::keystateA = GL_FALSE;
GLboolean Keystate::keystateD = GL_FALSE;
GLboolean Keystate::keystateF5 = GL_FALSE;
GLboolean Keystate::keystateSpace = GL_FALSE;
GLboolean Keystate::keystateLBtn = GL_FALSE;
GLboolean Keystate::keystateRBtn = GL_FALSE;
GLboolean Keystate::keystateQ = GL_FALSE;
GLboolean Keystate::keystateE = GL_FALSE;
GLboolean Keystate::keystateUp = GL_FALSE;
GLboolean Keystate::keystateLeft = GL_FALSE;
GLboolean Keystate::keystateDown = GL_FALSE;
GLboolean Keystate::keystateRight = GL_FALSE;
GLboolean Keystate::keystateRShift = GL_FALSE;
GLboolean Keystate::keystateF9 = GL_FALSE;
GLboolean Keystate::keystateF1 = GL_FALSE;
/*  _________________________________________________________________________*/
/*! key_callback

@param GLFWwindow*
Handle to window that is receiving event

@param int
the keyboard key that was pressed or released

@parm int
Platform-specific scancode of the key

@parm int
GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
for example E-mail and Play keys.

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when keyboard buttons are pressed.
When the ESC key is pressed, the close flag of the window is set.
*/
void Keystate::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true); // ESC ≈∞∞° ¥≠∑»¿ª ∂ß √¢¿ª ¥›¿Ω
    }

    updateKeyState(key, action, GLFW_KEY_SPACE, keystateSpace);
    updateKeyState(key, action, GLFW_KEY_F5, keystateF5);
    updateKeyState(key, action, GLFW_KEY_W, keystateW);
    updateKeyState(key, action, GLFW_KEY_S, keystateS);
    updateKeyState(key, action, GLFW_KEY_A, keystateA);
    updateKeyState(key, action, GLFW_KEY_D, keystateD);
    updateKeyState(key, action, GLFW_KEY_Q, keystateQ);
    updateKeyState(key, action, GLFW_KEY_E, keystateE);
    updateKeyState(key, action, GLFW_KEY_UP, keystateUp);
    updateKeyState(key, action, GLFW_KEY_LEFT, keystateLeft);
    updateKeyState(key, action, GLFW_KEY_DOWN, keystateDown);
    updateKeyState(key, action, GLFW_KEY_RIGHT, keystateRight);
    updateKeyState(key, action, GLFW_KEY_RIGHT_SHIFT, keystateRShift);
    updateKeyState(key, action, GLFW_KEY_F9, keystateF9);
    updateKeyState(key, action, GLFW_KEY_F1, keystateF1);
}


/*  _________________________________________________________________________*/
/*! updateKeyState

@param int
the keyboard key that was pressed or released

@param int
GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
for example E-mail and Play keys.

@parm int
Platform-specific scancode of the key

@parm GLBoolean
Key State Modify


@return none

This function is called when keyboard buttons are pressed.
When the ESC key is pressed, the close flag of the window is set.
*/

void Keystate::updateKeyState(const int& key, const int& action, const int& targetKey, GLboolean& keyState)
{
    if (key == targetKey && action == GLFW_PRESS)
    {
        keyState = true;
    }
    else if(key == targetKey && action == GLFW_RELEASE)
    {
        keyState = false;
    }

}

void Keystate::updateMouseKeyState(const int& key, const int& action, const int& targetKey, GLboolean& keyState)
{
    if (key == targetKey && action == GLFW_PRESS || key == targetKey && action == GLFW_REPEAT)
    {
        keyState = true;
    }
    else if (key == targetKey && action == GLFW_RELEASE)
    {
        keyState = false;
    }
    else
    {
        keyState = false;
    }
}

