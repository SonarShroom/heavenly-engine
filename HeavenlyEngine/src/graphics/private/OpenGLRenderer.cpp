#include "OpenGLRenderer.h"

#include <GLFW/glfw3.h>

using namespace Heavenly::Rendering;

int InitializeOpenGLRenderer()
{
    if (!glfwInit()) {
        printf("Could not init glfw. Exiting.");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Heavenly Game Engine", NULL, NULL);
    if (!window) {
        printf("Could not create glfw window. Exiting.");
        return -1;
    }

    glfwMakeContextCurrent(window);
}