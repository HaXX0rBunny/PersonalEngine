#include "Setting_window.h"
#include "Shader.h"
GLuint VAO, VBO,EBO, shader;


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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


   
    Shader  ourShader("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");
   
    // =============================================
   // CreateTriangle();
    CreateRectangle();
    //CreateShaderProgramFromFiles("../Extern/Shader/shader.vert", "../Extern/Shader/shader.frag");
    GameLoop(window, ourShader);
    ourShader.deleteProgram();  // 프로그램 종료 시 셰이더 삭제
    ClearBuffer();
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



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //4. when you want to draw use generated your shader program
        //glUseProgram(shader);// shader object will be use all shader & rendering order
        
        
        // set Uniform color
  /*      float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f / +0.5f;
        int vertexColorLocation = glGetUniformLocation(shader, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
        
        
        ourShader.use();
        
        //5. now we draw object
        glBindVertexArray(VAO);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    
        /* Poll for and process events */
     
    }
  
    glfwTerminate();
}




//GLuint AddShader(const char* shaderCode, GLenum shaderType)
//{
//    GLuint new_shader = glCreateShader(shaderType); // Referense ID generate Shader Object 
//
//    const GLchar* code[1];
//    code[0] = shaderCode;
//
//    glShaderSource(new_shader, 1, code, NULL); // shader Compile 1.shader objcet  2. how many strings 3. vertext shader real code 4. 
//
//    
//    //compile success check
//    GLint result = 0;
//    GLchar err_log[1024] = { 0 };
//
//    glCompileShader(new_shader);
//    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
//    if (!result)
//    {
//        glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << err_log << std::endl;
//        return 0;
//    }
//    return new_shader;
//}

//void CompileShader(const char* vsCode, const char* fsCode)
//{
//    GLuint vs, fs;
//    //shader pragram object fusion in many shader 
//    shader = glCreateProgram(); //generate programg & return Id
//
//    if (!shader)
//    {
//        printf("Error: Cannot create shader program.");
//        return;
//    }
//
//    vs = AddShader(vsCode, GL_VERTEX_SHADER);//vertex shader
//    fs = AddShader(fsCode, GL_FRAGMENT_SHADER);//fragment shader
//    glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
//    glAttachShader(shader, fs);
//
//    GLint result = 0;
//    GLchar err_log[1024] = { 0 };
//
//    glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.
//    glDeleteShader(vs);// after link useless shader delete
//    glDeleteShader(fs);
//    glGetProgramiv(shader, GL_LINK_STATUS, &result); // check to success link to program and shader
//    if (!result)
//    {
//        glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
//        printf("Error linking program: '%s'\n", err_log);
//        return;
//    }
//
//}

//void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath)
//{
//    std::string vsFile = ReadFile(vsPath);
//    std::string fsFile = ReadFile(fsPath);
//    const char* vsCode = vsFile.c_str();
//    const char* fsCode = fsFile.c_str();
//
//    CompileShader(vsCode, fsCode);
//}


//std::string ReadFile(const char* filePath)
//{
//    std::string content;
//    std::ifstream fileStream(filePath, std::ios::in);
//    if (!fileStream.is_open())
//    {
//        printf("Failed to read %s file! The file doesn't exit. \n", filePath);
//        return "";
//    }
//
//    std::string line = "";
//    while (!fileStream.eof())
//    {
//        std::getline(fileStream, line);
//        content.append(line + "\n");
//    }
//
//    fileStream.close();
//    return content;
//}
void CreateTriangle()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    //1)Vertex Array Object Binding
    glGenVertexArrays(1, &VAO); // 전역 VAO 사용 Create VertexBuffer ID
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO); // 전역 VBO 사용//Create buffer ID
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
    //    // 첫 번째 삼각형
    //     0.5f,  0.5f, 0.0f,  // 우측 상단
    //     0.5f, -0.5f, 0.0f,  // 우측 하단
    //    -0.5f,  0.5f, 0.0f,  // 좌측 상단 
    //    // second triangle
    //     0.5f, -0.5f, 0.0f,  // 우측 하단
    //    -0.5f, -0.5f, 0.0f,  // 좌측 하단
    //    -0.5f,  0.5f, 0.0f   // 좌측 상단
    //};
    //  float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};
    float vertices[] = {
        // 위치              // 컬러
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 우측 하단
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 좌측 하단
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 위 
    };
    //unsigned int indices[] = { 
    //0, 1, 3,   // 첫 번째 삼각형
    //1, 2, 3    // 두 번째 삼각형
    //};
    unsigned int indices[] = {
    0, 1, 2  // 한 개의 삼각형만 그리도록 인덱스 수정
    };
    //1)Vertex Array Object Binding
    glGenVertexArrays(1, &VAO); // 전역 VAO 사용 Create VertexBuffer ID

    glGenBuffers(1, &VBO); // 전역 VBO 사용//Create buffer ID
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    //2). vertex array copy in buffer to use Opengl
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding Buffer to GLARRAY_Buffer  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //2). index array copy in element buffer to use Opengl
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //3). to Set vertex attribute pointer
    // 위치 attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 컬러 attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //vertext attribute design  layout 0 , number of vertex attribute vec3 = 3, data type, nomalize gl_true (-1, 1),stride vertex attribute , offset


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CreateTexture()
{
    GLuint texture;
    glGenTextures(1, &texture);

    // 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    //텍스쳐 갯수 uint 배열에 텍스쳐 저장
    glBindTexture(GL_TEXTURE_2D, texture);
    //텍스처 바인딩
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        /*glTexImage2D
          = 이전에 로드된 이미지 데이터를 사용하여, 텍스처를 생성할 수 있음
          = 한번 호출하면 현재 바인딩된 객체가 첨부된 이미지를 가지게됨
          = mipmap을 사용하고 싶으면 glGenerateMipmap = > 현재 바인딩된 텍스처에 대해 자동 생성
          = 파라미터 1 : 텍스처 타겟을 지정(GL_TEXTURE_2D로 바인딩 된 객체에 텍스처 생성하겠다는 것)
          = = = =  GL_TEXTURE_1D, GL_TEXTURE_3D 로 바인딩된 객체에는 아무런 영향을 끼치지 않음
         = 파라미터 2 : mipmap 레벨을 수동으로 지정 (수작업으로 mipmap 만들 시)
         = 파라미터 3 : 텍스처가 어떤 포멧을 가져야하는지, 다룰 이미지는 RGB 값만 가지므로 GL_RGB
         = 파라미터 4~5 : 텍스처의 너비와 높이를 설정
         = 파라미터 6 : 항상 0 의 값이 되어야함. (legacy stuff)
         = 파라미터 7~8 : 원본 이미지의 포맷과 데이터 타입 지정,  RGB값이 있는 이미지를 로드, chars(bytes)로 저장한것
         = 파라미터 9 : 실제 이미지의 데이터
          */
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
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

void ClearBuffer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
