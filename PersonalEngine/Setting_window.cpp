#include "Setting_window.h"
#include "Shader.h"
#include "Level/TestLevel.h"
#include "GSM/GameStateManager.h"
#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/ShaderResource.h"
#include "Serializer/Serializer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

GSM::GameStateManager* gsm= nullptr;
int gGameRunning = 1;

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
    //==============================================================================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    //==============================================================================


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //Shader ourShader("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");


    ShaderResource* ourShader = new ShaderResource();
    ourShader->Load("../Extern/Shader/shader");


    Shader* shader = static_cast<Shader*>(ourShader->GetData());


    if (shader == nullptr)
    {
        std::cerr << "Failed to load shader" << std::endl;
        return -1;
    }
    /*===========================Game Init============================*/
   
  
    gsm = GSM::GameStateManager::GetInstance();
    gsm->ChangeLevel(new Level::TestLevel);
  
    /*=============================================================================================*/
    GameLoop(window, *shader);// Main Game Loop
    /*=============================================================================================*/
    ResourceManager::GetInstance()->Clear();
    ourShader->Unload();  // 프로그램 종료 시 셰이더 삭제
    delete ourShader;
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
    
    while (gsm->ShouldExit()==false&& !glfwWindowShouldClose(window))
    {

        processInput(window);
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

       

        gsm->Update();
        glfwPollEvents();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
    }

    gsm->Exit();
    gsm->DeleteGSM();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Serializer::Instance()->DestroyThis();
    glfwTerminate();
}



