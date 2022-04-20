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

bool Init(const Window::WindowContext* ctx = nullptr);

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
