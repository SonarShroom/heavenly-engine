#include "Rendering.h"

#include "BatchRendering.hpp"
#include "GUI.h"
#include "logging/LogManager.h"
#include "window/Window.h"

namespace Heavenly::Rendering
{

constexpr unsigned int VERTEX_ELEMENTS = 7;
constexpr unsigned int VERTEX_SIZE = VERTEX_ELEMENTS * sizeof(float);

unsigned int p_VAO = 0;
unsigned int p_VBO = 0;
unsigned int p_EBO = 0;

std::vector<RenderCommand> p_renderCommands;

bool Init(const Window::WindowContext* ctx)
{
	glGenVertexArrays(1, &p_VAO);
	glGenBuffers(1, &p_VBO);
	glGenBuffers(1, &p_EBO);
	
	glBindVertexArray(p_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
	
	GUI::InitDevGui(ctx);
	return true;
}

void Tick()
{
	constexpr auto _addVertexToBuffer = [](float* baseVecPos, const unsigned int nVertex, const Vertex* vertexVec) -> void
	{
		// Vertex data = [x, y, z],[r, g, b, a]
		for (unsigned int currVert = 0; currVert < nVertex; currVert++)
		{
			baseVecPos[currVert * 7] = vertexVec[currVert].position.x;
			baseVecPos[currVert * 7 + 1] = vertexVec[currVert].position.y;
			baseVecPos[currVert * 7 + 2] = vertexVec[currVert].position.z;

			baseVecPos[currVert * 7 + 3] = vertexVec[currVert].color.x;
			baseVecPos[currVert * 7 + 4] = vertexVec[currVert].color.y;
			baseVecPos[currVert * 7 + 5] = vertexVec[currVert].color.z;
			baseVecPos[currVert * 7 + 6] = vertexVec[currVert].color.w;
		}
	};

	// Calculate needed allocation for vertexes
	unsigned int _numberVertex = 0;
	unsigned int _numberElements = 0;
	for (const auto& _command : p_renderCommands)
	{
		switch (_command.type) {
			case RenderCommand::Type::DRAW_QUAD:
			{
				_numberVertex += 4;
				_numberElements += 6;
			} break;
			case RenderCommand::Type::DRAW_TRIANGLE:
			{
				_numberVertex += 3;
				_numberElements += 3;
			} break;
			default:
			{
				HV_LOG_ERROR("Invalid render command passed to renderer.");
			} break;
		}
	}

	float* _vertexData = new float[_numberVertex * 7];
	unsigned int* _elements = new unsigned int[_numberElements];
	unsigned int _currentMinVertIndex = 0;
	unsigned int _currentMinElemIndex = 0;
	unsigned int _currentMinElement = 0;
	
	for (const auto& _command : p_renderCommands)
	{
		switch (_command.type) {
			case RenderCommand::Type::DRAW_QUAD:
			{
				_addVertexToBuffer(_vertexData + _currentMinVertIndex * 7, 4, _command.payload.quad.verts);
				_currentMinVertIndex += 4;

				_elements[_currentMinElemIndex] = _currentMinElement;
				_elements[_currentMinElemIndex + 1] = _currentMinElement + 1;
				_elements[_currentMinElemIndex + 2] = _currentMinElement + 2;
				_elements[_currentMinElemIndex + 3] = _currentMinElement + 1;
				_elements[_currentMinElemIndex + 4] = _currentMinElement + 3;
				_elements[_currentMinElemIndex + 5] = _currentMinElement + 2;
				_currentMinElemIndex += 6;
				_currentMinElement += 4;
			} break;
			case RenderCommand::Type::DRAW_TRIANGLE:
			{
				_addVertexToBuffer(_vertexData + _currentMinVertIndex, 3, _command.payload.triangle.verts);
				_currentMinVertIndex += 3;

				_elements[_currentMinElemIndex] = _currentMinElemIndex;
				_elements[_currentMinElemIndex + 1] = _currentMinElemIndex + 1;
				_elements[_currentMinElemIndex + 2] = _currentMinElemIndex + 2;
				_currentMinElemIndex += 3;
				_currentMinElement += 3;
			} break;
			default: {} break;
		}
	}

	glBindVertexArray(p_VAO);
	glBufferData(GL_ARRAY_BUFFER, _numberVertex * 7 * sizeof(float), _vertexData, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberElements * sizeof(unsigned int), _elements, GL_DYNAMIC_DRAW);

	glDrawElements(GL_TRIANGLES, _numberElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	GUI::ShowDevGui();

	Window::SwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT);

	delete[] _vertexData;
	delete[] _elements;
}

void Terminate()
{
	glDeleteVertexArrays(1, &p_VAO);
	glDeleteBuffers(1, &p_VBO);
	glDeleteBuffers(1, &p_EBO);
	GUI::Terminate();
}

void EmitQuadCommand(const Quad* quad)
{
	RenderCommand _newCmd = {};
	_newCmd.type = RenderCommand::Type::DRAW_QUAD;
	_newCmd.payload.quad = *quad;
	p_renderCommands.push_back(_newCmd);
}

void EmitTriangleCommand(const Triangle* triangle)
{
	RenderCommand _newCmd = {};
	_newCmd.type = RenderCommand::Type::DRAW_TRIANGLE;
	_newCmd.payload.triangle = *triangle;
	p_renderCommands.push_back(_newCmd);
}

void UseShaderProgram(const unsigned int shaderProgram)
{
	glUseProgram(shaderProgram);
}

bool RegisterNewVertexShader(const std::string& shaderSource, unsigned int& shaderId)
{
	shaderId = glCreateShader(GL_VERTEX_SHADER);

	const char* _shaderCStr = shaderSource.c_str();
	glShaderSource(shaderId, 1, &_shaderCStr, nullptr);
	glCompileShader(shaderId);

	return CheckShaderCompilationSuccess(shaderId);
}

bool RegisterNewFragmentShader(const std::string& shaderSource, unsigned int& shaderId)
{
	shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	const char* shaderCStr = shaderSource.c_str();
	glShaderSource(shaderId, 1, &shaderCStr, nullptr);
	glCompileShader(shaderId);

	return CheckShaderCompilationSuccess(shaderId);
}

void DeleteShader(const unsigned int shaderId)
{
	glDeleteShader(shaderId);
}

bool CheckShaderCompilationSuccess(const int shaderId)
{
	int success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (success)
	{
		return true;
	}

	char infoLog[512] {0};
	glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
	HV_LOG_ERROR("Error on shader compilation: {}", infoLog);
	return false;
}

bool RegisterNewShaderProgram(const unsigned int vertex_shader_id, const unsigned int frag_shader_id, unsigned int& shader_program_id)
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

}
