#include "Setting_window.h"
#include "Shader.h"
#include "GSM/GameStateManager.h"
GLuint shader;
GSM::GameStateManager* gsm= nullptr;
int setWindow_()
{
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// (Option name ,option value)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 더 이상 쓰이지 않는 하위 호환 기능들 에러 처리
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 상위 호환성 지원
    //GLFWmonitor* primary = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(Window_width, Window_height, " Biginner", NULL, NULL);//width height title fullscreen(GLFWmonitor*) subscreen
    gsm = GSM::GameStateManager::GetInstance();
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate(); // 초기화 실패 시 GLFW 종료
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    Shader ourShader("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");
    /*=============================================================================================*/
    GameLoop(window, ourShader);// Main Game Loop
    /*=============================================================================================*/

    ourShader.deleteProgram();  // 프로그램 종료 시 셰이더 삭제

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, Window_width, Window_height);
}



void GameLoop(GLFWwindow* window, Shader& ourShader)
{

    //Todo Gamelooping in this lopp ==========================================================
/* Loop until the user closes the window */



    while (gsm->ShouldExit() == false)
    {
        processInput(window);
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        ourShader.use();
        
        gsm->Update();


        glfwPollEvents();
        glfwSwapBuffers(window);
    
        /* Poll for and process events */
     
    }
    gsm->DeleteGSM();
    glfwTerminate();
}



