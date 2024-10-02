#include "Setting_window.h"

GLuint VAO, VBO, shader;


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
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate(); // 초기화 실패 시 GLFW 종료
        return -1;
    }
    // =============================================
    CreateTriangle();
    CreateShaderProgramFromFiles("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");
    GameLoop(window);


    return 0;
}

void GameLoop(GLFWwindow* window)
{

    //Todo Gamelooping in this lopp ==========================================================
/* Loop until the user closes the window */



    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}




GLuint AddShader(const char* shaderCode, GLenum shaderType)
{
    GLuint new_shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    glShaderSource(new_shader, 1, code, NULL);

    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glCompileShader(new_shader);
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
        printf("Error compiling the %d shader: '%s'\n", shaderType, err_log);
        return 0;
    }
    return new_shader;
}

void CompileShader(const char* vsCode, const char* fsCode)
{
    GLuint vs, fs;

    shader = glCreateProgram();

    if (!shader)
    {
        printf("Error: Cannot create shader program.");
        return;
    }

    vs = AddShader(vsCode, GL_VERTEX_SHADER);
    fs = AddShader(fsCode, GL_FRAGMENT_SHADER);
    glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
    glAttachShader(shader, fs);

    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
        printf("Error linking program: '%s'\n", err_log);
        return;
    }
}

void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath)
{
    std::string vsFile = ReadFile(vsPath);
    std::string fsFile = ReadFile(fsPath);
    const char* vsCode = vsFile.c_str();
    const char* fsCode = fsFile.c_str();

    CompileShader(vsCode, fsCode);
}


std::string ReadFile(const char* filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open())
    {
        printf("Failed to read %s file! The file doesn't exit. \n", filePath);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
void CreateTriangle()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO); // 전역 VAO 사용
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO); // 전역 VBO 사용
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
