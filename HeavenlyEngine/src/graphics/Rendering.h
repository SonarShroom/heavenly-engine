#ifndef RENDERERING_H_
#define RENDERERING_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"
#include "RenderPrimitives.h"

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

void EmitQuadCommand(const Quad* quad);

void EmitTriangleCommand(const Triangle* triangle);

void UseShaderProgram(const unsigned int shaderProgram);

// Shader compilation functions
bool RegisterNewVertexShader(const std::string& shader_source, unsigned int& shader_id);

bool RegisterNewFragmentShader(const std::string& shader_source, unsigned int& shader_id);

void DeleteShader(const unsigned int shaderId);

bool RegisterNewShaderProgram(const unsigned int vertex_shader_id, const unsigned int frag_shader_id, unsigned int& shader_program_id);

bool CheckShaderProgramLinkingError(const int shader_program_id);

bool CheckShaderCompilationSuccess(const int shader_id);

}

#endif //RENDERERING_H_
