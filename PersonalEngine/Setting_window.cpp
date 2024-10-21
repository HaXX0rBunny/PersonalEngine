#include "Setting_window.h"


GLFWwindow* SetWindow::window = nullptr;
GSM::GameStateManager* SetWindow::gsm = nullptr;
int SetWindow::gGameRunning = 1;

std::string SetWindow::title;
GLint SetWindow::width;
GLint SetWindow::height;

int SetWindow::setWindow_()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    init(Window_width, Window_height, EngineTitle); // 초기화

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    GameLoop(window); // 메인 게임 루프

    cleanup(); // 프로그램 종료 시 자원 정리
    return 0;
}

void SetWindow::init(GLint width, GLint height, std::string title)
{
    SetWindow::width = width;
    SetWindow::height = height;
    SetWindow::title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

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
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetKeyCallback(window, Keystate::key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gsm = GSM::GameStateManager::GetInstance();
    gsm->ChangeLevel(new Level::TestLevel);
}

void SetWindow::draw(Shader& shader)
{


    Time::update_time();
    std::stringstream sstr;
    sstr << std::fixed << EngineTitle << " | " << std::setprecision(2) << "FPS : " << Time::fps;
    glfwSetWindowTitle(window, sstr.str().c_str());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    MainMenuEditor::TopBar();

    gsm->Update();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void SetWindow::cleanup()
{
    gsm->Exit();
    gsm->DeleteGSM();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Serializer::Instance()->DestroyThis();

    ResourceManager::GetInstance()->Clear();
 
    glfwTerminate();
 
}




void SetWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, Window_width, Window_height);
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
        EngineState::UpdateEnigneState();
        glfwSwapBuffers(window);
    }

    ourShader->Unload();
    delete ourShader;


}

