#include "Renderer.h"

#include "BatchRendering.hpp"

#include "logging/LogManager.h"

#include "resources/Shader.h"

#include "world/Component.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::Graphics
{

constexpr unsigned int VERTEX_ELEMENTS = 7;
constexpr unsigned int VERTEX_SIZE = VERTEX_ELEMENTS * sizeof(float);

Renderer::Renderer(const int viewportWidth, const int viewportHeight)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		HV_LOG_INFO("Could not initialize GLAD. Exiting.");
		return;
	}

	HV_LOG_INFO("OpenGL initialized. Version: {}", (const char*) glGetString(GL_VERSION));

	glViewport(0, 0, viewportWidth, viewportHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::Tick([[maybe_unused]] const float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT);

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
	for (const auto& _command : renderCommands)
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
			case RenderCommand::Type::USE_SHADER: break;
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
	
	for (const auto& _command : renderCommands)
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
			case RenderCommand::Type::USE_SHADER:
			{
				glUseProgram(_command.payload.shaderProgramID);
			} break;
			default: {} break;
		}
	}

	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, _numberVertex * 7 * sizeof(float), _vertexData, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberElements * sizeof(unsigned int), _elements, GL_DYNAMIC_DRAW);

	glDrawElements(GL_TRIANGLES, _numberElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	delete[] _vertexData;
	delete[] _elements;
	renderCommands.clear();
}

void Renderer::RectRendererSystem(World::RectComponent& rectComponent, [[maybe_unused]] const float timeDelta)
{
	if (rectComponent.drawDirty)
	{
		const auto _transformPos = rectComponent.GetSibling<World::TransformComponent>()->position;
		const auto _size = rectComponent.size;
		rectComponent.quad.verts[0] = {
			{_transformPos.x, _transformPos.y, _transformPos.z},
			rectComponent.color,
			{}
		};
		rectComponent.quad.verts[1] = {
			{_transformPos.x, _transformPos.y - _size.y, _transformPos.z},
			rectComponent.color,
			{}
		};
		rectComponent.quad.verts[2] = {
			{_transformPos.x + _size.x, _transformPos.y, _transformPos.z},
			rectComponent.color,
			{}
		};
		rectComponent.quad.verts[3] = {
			{_transformPos.x + _size.x, _transformPos.y - _size.y, _transformPos.z},
			rectComponent.color,
			{}
		};
		rectComponent.drawDirty = false;
	}

	EmitQuadCommand(&rectComponent.quad);
}

void Renderer::MaterialRendererSystem(World::MaterialComponent& material, [[maybe_unused]] const float deltaTime)
{
	if (material.shader)
	{
		EmitUseShaderCommand(*material.shader);
	}
}

void Renderer::EmitTriangleCommand(const Triangle* triangle)
{
	RenderCommand _newCmd = {};
	_newCmd.type = RenderCommand::Type::DRAW_TRIANGLE;
	_newCmd.payload.triangle = *triangle;
	renderCommands.push_back(_newCmd);
}

void Renderer::EmitQuadCommand(const Quad* quad)
{
	RenderCommand _newCmd = {};
	_newCmd.type = RenderCommand::Type::DRAW_QUAD;
	_newCmd.payload.quad = *quad;
	renderCommands.push_back(_newCmd);
}

void Renderer::EmitUseShaderCommand(const Resources::Shader& shader)
{
	RenderCommand _newCmd = {};
	_newCmd.type = RenderCommand::Type::USE_SHADER;
	_newCmd.payload.shaderProgramID = shader.GetProgramID();
	renderCommands.push_back(_newCmd);
}

}
