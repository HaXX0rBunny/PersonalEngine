#include "Setting_window.h"

void SetWindow::GameLoop(GLFWwindow* window)
{
    //Todo Gamelooping in this lopp ==========================================================
/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}



int SetWindow::setWindow()
{
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// (Option name ,option value)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �� �̻� ������ �ʴ� ���� ȣȯ ��ɵ� ���� ó��
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���� ȣȯ�� ����


    //GLFWmonitor* primary = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(Window_width, Window_height, " Biginner", NULL, NULL);//width height title fullscreen subscreen
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // =============================================
    GameLoop(window);


    return 0;
}

