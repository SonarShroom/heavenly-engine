#include "Rendering.h"

#include <iostream>

#include "Rect.h"

using namespace Heavenly::Rendering;

RenderableComponent::RenderableComponent()
{
    glGenBuffers(1, &vertex_buffer_object_id);
}

void RenderableComponent::SetVBOData(void* data, std::vector<VertexDataDescriptor> data_descriptors)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_id);

    unsigned int current_data_descriptor = 0;
    for(auto descriptor : data_descriptors)
    {
        glVertexAttribPointer(
            current_data_descriptor,
            descriptor.data_size,
            )
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

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

    for(auto* renderable : renderable_components)
    {
        glBindBuffer(GL_ARRAY_BUFFER, renderable->vertex_buffer_object_id);

    }

    glfwSwapBuffers(render_context->window);

    glfwPollEvents();
}

bool Renderer::ShouldCloseWindow()
{
    return glfwWindowShouldClose(render_context->window);
}

void Renderer::CreateRect()
{
    Rect* new_rect = new Rect();
    renderable_components.push_back(new_rect->GetRenderableComponent());
}