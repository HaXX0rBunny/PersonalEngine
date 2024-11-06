#include "Setting_window.h"
GLFWwindow* window;
GSM::GameStateManager* SetWindow::gsm = nullptr;
GEM::GameEditorManager* SetWindow::gem = nullptr;
int SetWindow::gGameRunning = 1;



int SetWindow::setWindow_()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    init(); // 초기화

    GameLoop(window); // 메인 게임 루프

    cleanup(); // 프로그램 종료 시 자원 정리
    return 0;
}

void SetWindow::init()
{


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(Window_width, Window_height, EngineTitle, NULL, NULL);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate();
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();



    glfwSetKeyCallback(window, Keystate::key_callback);



    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gsm = GSM::GameStateManager::GetInstance();
    gsm->ChangeLevel(new Level::TestLevel);
    gem = GEM::GameEditorManager::GetInstance();
    gem->Init();


    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDepthFunc(GL_LESS);

    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
}

void SetWindow::draw(Shader& shader)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Time::update_time();
    std::stringstream sstr;
    sstr << std::fixed << EngineTitle << " | " << std::setprecision(2) << "MODE : " << EngineState::engineState_ << "FPS : " << Time::fps ;
    glfwSetWindowTitle(window, sstr.str().c_str());
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    gem->Update();
    gsm->Update();



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}


void SetWindow::cleanup()
{

  //  glDisable(GL_BLEND);
    gsm->Exit();
    gsm->DeleteGSM();
    gem->DeleteGEM();

    // IMGUI 종료
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    // 리소스 정리
    Serializer::Instance()->DestroyThis();
    ResourceManager::GetInstance()->Clear();
    DEBUG_PROFILER_DELETE;
    // GLFW 종료
    glfwTerminate();
 
}




void SetWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}






void SetWindow::GameLoop(GLFWwindow* window)
{
    //Todo Gamelooping in this lopp ==========================================================
/* Loop until the user closes the window */

    ShaderResource* ourShader = new ShaderResource();
    ourShader->Load("../Extern/Shader/shader");
    Shader* shader = static_cast<Shader*>(ourShader->GetData());

    if (shader == nullptr)
    {
        std::cerr << "Failed to load shader" << std::endl;
        return;
    }

    while (gsm->ShouldExit() == false && !glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        draw(*shader);

        glfwSwapBuffers(window);
    }

    ourShader->Unload();
    delete ourShader;


}

