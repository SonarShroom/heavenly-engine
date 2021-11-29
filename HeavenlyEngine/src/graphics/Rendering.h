#ifndef RENDERERING_H_
#define RENDERERING_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Heavenly
{
namespace Rendering
{
struct Vertex
{
    Math::Vector3 position      {0, 0, 0};
    //Math::Vector4 color         {255, 255, 255, 255};
    //Math::Vector2 uv            {0, 0};
};

struct VertexDataDescriptor
{
    std::size_t data_size = 0;
    std::size_t data_offset = 0;
    int data_type = GL_FLOAT;
    bool is_normalized = false;
    std::size_t elements = 0;   // NOTE: what was this here for?
};

struct RenderContext
{
    Math::Vector2 window_resolution = Math::Vector2(1280, 720);
    GLFWwindow* window = nullptr;
};

class RenderableComponent
{
public:
    RenderableComponent();

    void SetVBOData(void* data, std::size_t data_size, std::vector<VertexDataDescriptor> data_descriptors);

    unsigned int vertex_buffer_object_id    { 0 };
    unsigned int vertex_array_object_id     { 0 };
    unsigned int shader_program_id          { 0 };
};

int Init(int window_width = 1280, int window_height = 720);

void Tick(float time_delta);

bool ShouldCloseWindow();

void Terminate();

bool RegisterNewVertexShader(const char* shader_source, int& shader_id);

bool RegisterNewFragmentShader(const char* shader_source, int& shader_id);

bool RegisterNewShaderProgram(int vertex_shader_id, int frag_shader_id, int& shader_program_id);

//Creates rect at the center of the screen
void CreateRect();

//Creates rect at the center of the screen with target shader program
void CreateRect(const int shader_program_id);

bool CheckShaderProgramLinkingError(const int shader_program_id);

bool CheckShaderCompilationSuccess(const int shader_id);

}
}

#endif //RENDERERING_H_
