#ifndef RENDERERING_H_
#define RENDERERING_H_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MathBaseTypes.h"
#include "RenderPrimitives.h"

namespace Heavenly::Window
{
	struct WindowContext;
}

namespace Heavenly::Rendering
{

bool Init();

void Tick(const float deltaTime);

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
