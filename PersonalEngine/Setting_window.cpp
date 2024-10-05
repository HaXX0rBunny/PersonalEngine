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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �� �̻� ������ �ʴ� ���� ȣȯ ��ɵ� ���� ó��
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���� ȣȯ�� ����
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
        glfwTerminate(); // �ʱ�ȭ ���� �� GLFW ����
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // =============================================
   // CreateTriangle();
    CreateRectangle();
    CreateShaderProgramFromFiles("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");
    GameLoop(window);


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



void GameLoop(GLFWwindow* window)
{

    //Todo Gamelooping in this lopp ==========================================================
/* Loop until the user closes the window */



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //4. when you want to draw use generated your shader program
        glUseProgram(shader);// shader object will be use all shader & rendering order
        
        
        // set Uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f / +0.5f;
        int vertexColorLocation = glGetUniformLocation(shader, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        
        
        
        
        //5. now we draw object
        glBindVertexArray(VAO);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    
        /* Poll for and process events */
     
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);
    glfwTerminate();
}




GLuint AddShader(const char* shaderCode, GLenum shaderType)
{
    GLuint new_shader = glCreateShader(shaderType); // Referense ID generate Shader Object 

    const GLchar* code[1];
    code[0] = shaderCode;

    glShaderSource(new_shader, 1, code, NULL); // shader Compile 1.shader objcet  2. how many strings 3. vertext shader real code 4. 

    
    //compile success check
    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glCompileShader(new_shader);
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << err_log << std::endl;
        return 0;
    }
    return new_shader;
}

void CompileShader(const char* vsCode, const char* fsCode)
{
    GLuint vs, fs;
    //shader pragram object fusion in many shader 
    shader = glCreateProgram(); //generate programg & return Id

    if (!shader)
    {
        printf("Error: Cannot create shader program.");
        return;
    }

    vs = AddShader(vsCode, GL_VERTEX_SHADER);//vertex shader
    fs = AddShader(fsCode, GL_FRAGMENT_SHADER);//fragment shader
    glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
    glAttachShader(shader, fs);

    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.
    glDeleteShader(vs);// after link useless shader delete
    glDeleteShader(fs);
    glGetProgramiv(shader, GL_LINK_STATUS, &result); // check to success link to program and shader
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
    //1)Vertex Array Object Binding
    glGenVertexArrays(1, &VAO); // ���� VAO ��� Create VertexBuffer ID
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO); // ���� VBO ���//Create buffer ID
    //2). vertex array copy in buffer to use Opengl
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding Buffer to GLARRAY_Buffer  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //3). to Set vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    //vertext attribute design  layout 0 , number of vertex attribute vec3 = 3, data type, nomalize gl_true (-1, 1),stride vertex attribute , offset
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CreateRectangle()
{
    //float vertices[] = {
    //    // ù ��° �ﰢ��
    //     0.5f,  0.5f, 0.0f,  // ���� ���
    //     0.5f, -0.5f, 0.0f,  // ���� �ϴ�
    //    -0.5f,  0.5f, 0.0f,  // ���� ��� 
    //    // second triangle
    //     0.5f, -0.5f, 0.0f,  // ���� �ϴ�
    //    -0.5f, -0.5f, 0.0f,  // ���� �ϴ�
    //    -0.5f,  0.5f, 0.0f   // ���� ���
    //};
    //  float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};
    float vertices[] = {
        // ��ġ              // �÷�
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ���� �ϴ�
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���� �ϴ�
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // �� 
    };
    unsigned int indices[] = { 
    0, 1, 3,   // ù ��° �ﰢ��
    1, 2, 3    // �� ��° �ﰢ��
    };
    GLuint EBO;
    //1)Vertex Array Object Binding
    glGenVertexArrays(1, &VAO); // ���� VAO ��� Create VertexBuffer ID

    glGenBuffers(1, &VBO); // ���� VBO ���//Create buffer ID
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    //2). vertex array copy in buffer to use Opengl
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding Buffer to GLARRAY_Buffer  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //2). index array copy in element buffer to use Opengl
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //3). to Set vertex attribute pointer
    // ��ġ attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // �÷� attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //vertext attribute design  layout 0 , number of vertex attribute vec3 = 3, data type, nomalize gl_true (-1, 1),stride vertex attribute , offset


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ClearShader()// when use to more need shader or change shader
{
    // Stop using the current shader program
    glUseProgram(0);

    // Delete the shader program if it was created
    if (shader != 0)
    {
        glDeleteProgram(shader);
        shader = 0; // Reset the shader ID to avoid using an invalid program
    }
}
