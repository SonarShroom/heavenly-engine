#ifndef RENDERERING_H_
#define RENDERERING_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Heavenly::Window
{
	struct WindowContext;
}

namespace Heavenly::Rendering
{

struct Vertex
{
    Math::Vector3<float> position      {0, 0, 0};
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

//class RenderableComponent
//{
//public:
//    RenderableComponent();
//
//    void SetVBOData(void* data, std::size_t data_size, std::vector<VertexDataDescriptor> data_descriptors);
//
//    unsigned int vertex_buffer_object_id    { 0 };
//    unsigned int vertex_array_object_id     { 0 };
//    unsigned int shader_program_id          { 0 };
//};

int Init(const Window::WindowContext* ctx = nullptr);

void Tick();

void Terminate();

std::vector<unsigned int> InitVertexBufferObjects(const unsigned int numBuffers);

void BindBuffer(const unsigned int bufferId);

void DeleteBuffers(const std::vector<unsigned int>& bufferIds);

std::vector<unsigned int> InitVertexArrayObjects(const unsigned int numBuffers);

void BindArray(const unsigned int arrayId);

void DrawArrays(const unsigned int firstElem, const unsigned int count);

void DeleteArrays(const std::vector<unsigned int>& arrayIds);

// TODO: Remove these once batch rendering is implemented, since they most likely won't be needed.

void BufferStaticData(const unsigned int dataSize, const void* data);

void SetVertexAttribute(const unsigned int index, const unsigned int dataSize, const unsigned int stride);

void UseShaderProgram(const unsigned int shaderProgram);

// Shader compilation functions
bool RegisterNewVertexShader(const std::string& shader_source, unsigned int& shader_id);

bool RegisterNewFragmentShader(const std::string& shader_source, unsigned int& shader_id);

void DeleteShader(const unsigned int shaderId);

bool RegisterNewShaderProgram(const unsigned int vertex_shader_id, const unsigned int frag_shader_id, unsigned int& shader_program_id);

//Creates rect at the center of the screen
void CreateRect();

//Creates rect at the center of the screen with target shader program
void CreateRect(const int shader_program_id);

bool CheckShaderProgramLinkingError(const int shader_program_id);

bool CheckShaderCompilationSuccess(const int shader_id);

}

#endif //RENDERERING_H_
