#include "Rendering.h"

#include "BatchRendering.hpp"
#include "GUI.h"
#include "logging/LogManager.h"
#include "RenderPrimitives.h"
#include "window/Window.h"

namespace Heavenly::Rendering
{

constexpr unsigned int VERTEX_SIZE = 7 * sizeof(float);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	GUI::InitDevGui(ctx);
	return true;
}

void Tick()
{
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

	// Vertex data = [x, y, z],[r, g, b, a]
	float* _vertexData = new float[_numberVertex * 7];
	unsigned int* _elements = new unsigned int[_numberElements];

	glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData), _vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_elements), _elements, GL_STATIC_DRAW);
	GUI::ShowDevGui();

	Window::SwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT);

	// for(auto* renderable : m_renderableComponents)
	// {
	// 	glUseProgram(renderable->shader_program_id);
	// 	glBindVertexArray(renderable->vertex_array_object_id);
	// 	glDrawArrays(GL_TRIANGLES, 0, 3);
	// }
}

void Terminate()
{
	GUI::Terminate();
}

std::vector<unsigned int> InitVertexBufferObjects(const unsigned int numBuffers)
{
	std::vector<unsigned int> _bufferObjIds(numBuffers, 0);
	glGenBuffers(numBuffers, _bufferObjIds.data());
	return _bufferObjIds;
}

void BindBuffer(const unsigned int bufferId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void DeleteBuffers(const std::vector<unsigned int>& bufferIds)
{
	glDeleteBuffers((unsigned int)bufferIds.size(), bufferIds.data());
}

std::vector<unsigned int> InitVertexArrayObjects(const unsigned int numBuffers)
{
	std::vector<unsigned int> _arrayObjIds(numBuffers, 0);
	glGenVertexArrays(numBuffers, _arrayObjIds.data());
	return _arrayObjIds;
}

void BindArray(const unsigned int arrayId)
{
	glBindVertexArray(arrayId);
}

void DrawArrays(const unsigned int firstElem, const unsigned int count)
{
	glDrawArrays(GL_TRIANGLES, firstElem, count);
}

void DeleteArrays(const std::vector<unsigned int>& arrayIds)
{
	glDeleteVertexArrays((unsigned int)arrayIds.size(), arrayIds.data());
}

void BufferStaticData(const unsigned int dataSize, const void* data)
{
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void SetVertexAttribute(const unsigned int index, const unsigned int dataSize, const unsigned int stride)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, dataSize, GL_FLOAT, GL_FALSE, stride, (void*)0);
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

void CreateRect()
{
	// Rect* new_rect = new Rect();
	// m_renderableComponents.push_back(new_rect->GetRenderableComponent());
}

void CreateRect([[maybe_unused]] const int shader_program_id)
{
	// Rect* new_rect = new Rect();
	// new_rect->SetShader(shader_program_id);
	// m_renderableComponents.push_back(new_rect->GetRenderableComponent());
}

}
