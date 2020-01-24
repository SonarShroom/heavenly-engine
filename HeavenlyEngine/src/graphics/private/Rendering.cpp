#include "Rendering.h"

#include <iostream>

using namespace Heavenly::Rendering;

int Renderer::InitContext()
{
    if (!glfwInit()) {
        std::cout << "Could not init glfw. Exiting." << std::endl;
        return -1;
    }

    render_context = new RenderContext();
    render_context->window = glfwCreateWindow(1280, 720, "Heavenly Game Engine", NULL, NULL);
    if (!render_context->window) {
        std::cout << "Could not create glfw window. Exiting." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(render_context->window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Could not initialize GLAD. Exiting." << std::endl;
        return -1;
    }

    std::cout << "OpenGL initialized. Version: " << glGetString(GL_VERSION) << std::endl;
    return 0;
}

void Renderer::Tick(float time_delta)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(render_context->window);

    glfwPollEvents();
}

bool Renderer::ShouldCloseWindow()
{
    return glfwWindowShouldClose(render_context->window);
}