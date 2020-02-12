#include "Rendering.h"

#include <iostream>

using namespace Heavenly::Rendering;

Renderer::~Renderer()
{
    if(render_context)
    {
        std::cout << "Destroying render context..." << std::endl;
        glfwDestroyWindow(render_context->window);
        delete render_context;
    }
}

int Renderer::InitContext(int window_width, int window_height, bool window_resizable)
{
    if (!glfwInit()) {
        std::cout << "Could not init glfw. Exiting." << std::endl;
        return -1;
    }

    render_context = new RenderContext();
    render_context->window_resolution = {(float)window_width, (float)window_width};
    render_context->window_resizable = window_resizable;
    render_context->window = glfwCreateWindow(window_width, window_height, "Heavenly Game Engine", NULL, NULL);
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