#include "OpenGLRenderer.h"

#include <iostream>

int Heavenly::Rendering::Renderer::InitContext()
{
    if (!glfwInit()) {
        std::cout << "Could not init glfw. Exiting." << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Heavenly Game Engine", NULL, NULL);
    if (!window) {
        std::cout << "Could not create glfw window. Exiting." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Could not initialize GLAD. Exiting." << std::endl;
        return -1;
    }

    std::cout << "OpenGL initialized. Version: " << glGetString(GL_VERSION) << std::endl;
    return 0;
}