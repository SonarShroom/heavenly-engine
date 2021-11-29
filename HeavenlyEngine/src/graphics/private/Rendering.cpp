#include "Rendering.h"

#include <iostream>

#include "Rect.h"
#include "LogManager.h"

using namespace Heavenly::Rendering;

namespace Heavenly
{

namespace Rendering
{

RenderContext _renderingCtx;

std::vector<RenderableComponent*> _renderable_components;

RenderableComponent::RenderableComponent()
{
    glGenVertexArrays(1, &vertex_array_object_id);
    glGenBuffers(1, &vertex_buffer_object_id);
}

void RenderableComponent::SetVBOData(void* data, std::size_t data_size, std::vector<VertexDataDescriptor> data_descriptors)
{
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_id);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    unsigned int current_data_descriptor = 0;
    for(auto descriptor : data_descriptors)
    {
        glVertexAttribPointer(
            current_data_descriptor,
            descriptor.data_size,
            descriptor.data_type,
            descriptor.is_normalized ? GL_TRUE : GL_FALSE,
            3 * sizeof(float),
            (void*)0
        );
        glEnableVertexAttribArray(current_data_descriptor);
        current_data_descriptor++;
    }
}

int Init(int window_width, int window_height)
{
    if (!glfwInit()) {
        HV_LOG_ERROR("Could not init glfw. Exiting.");
        return -1;
    }

    _renderingCtx.window_resolution = {(float)window_width, (float)window_width};
    _renderingCtx.window = glfwCreateWindow(window_width, window_height, "Heavenly Game Engine", NULL, NULL);
    if (!_renderingCtx.window) {
        HV_LOG_INFO("Could not create glfw window. Exiting.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_renderingCtx.window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        HV_LOG_INFO("Could not initialize GLAD. Exiting.");
        return -1;
    }

    HV_LOG_INFO("OpenGL initialized. Version: {}", glGetString(GL_VERSION));
    return 0;
}

void Terminate()
{
    HV_LOG_INFO("Destroying render context...");
    if (_renderingCtx.window != nullptr)
    {
        glfwDestroyWindow(_renderingCtx.window);
        _renderingCtx.window = nullptr;
    }
}

void Tick(float time_delta)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto* renderable : _renderable_components)
    {
        glUseProgram(renderable->shader_program_id);
        glBindVertexArray(renderable->vertex_array_object_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glfwSwapBuffers(_renderingCtx.window);

    glfwPollEvents();
}

bool RegisterNewVertexShader(const char* shader_source, int& shaderId)
{
    shaderId = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shaderId, 1, &shader_source, nullptr);
    glCompileShader(shaderId);

    return CheckShaderCompilationSuccess(shaderId);
}

bool RegisterNewFragmentShader(const char* shader_source, int& shader_id)
{
    shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader_id, 1, &shader_source, nullptr);
    glCompileShader(shader_id);

    return CheckShaderCompilationSuccess(shader_id);
}

bool CheckShaderCompilationSuccess(const int shader_id)
{
    int success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (success)
    {
        return true;
    }

    char infoLog[512] {0};
    glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
    HV_LOG_ERROR("Error on shader compilation: {}", infoLog);
    return false;
}

bool RegisterNewShaderProgram(int vertex_shader_id, int frag_shader_id, int& shader_program_id)
{
    shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, frag_shader_id);
    glLinkProgram(shader_program_id);

    // NOTE: Should we really delete the shaders here?
    glDeleteShader(vertex_shader_id);
    glDeleteShader(frag_shader_id);

    return CheckShaderProgramLinkingError(shader_program_id);
}

bool CheckShaderProgramLinkingError(const int shader_program_id)
{
    int success = 0;
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (success)
    {
        return true;
    }

    char infoLog[512]{ 0 };
    glGetProgramInfoLog(shader_program_id, 512, NULL, infoLog);
    HV_LOG_ERROR("Oh shit my boy we got the following linking error: {}", infoLog);
    return false;
}

bool ShouldCloseWindow()
{
    return glfwWindowShouldClose(_renderingCtx.window);
}

void CreateRect()
{
    Rect* new_rect = new Rect();
    _renderable_components.push_back(new_rect->GetRenderableComponent());
}

void CreateRect(const int shader_program_id)
{
    Rect* new_rect = new Rect();
    new_rect->SetShader(shader_program_id);
    _renderable_components.push_back(new_rect->GetRenderableComponent());
}

}

}
