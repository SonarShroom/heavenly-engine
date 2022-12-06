#include "world/RenderingComponents.h"

#include "graphics/Rendering.h"

namespace Heavenly::World
{

void MaterialRendererSystem(MaterialComponent& material, [[maybe_unused]] const float deltaTime)
{
	if (!material.compiled)
	{
		unsigned int _vertShaderIndex = 0;
		unsigned int _fragShaderIndex = 0;
		
		if (!material.vertexShader.empty())
		{
			Rendering::RegisterNewVertexShader(material.vertexShader, _vertShaderIndex);
		}

		if (!material.fragmentShader.empty())
		{
			Rendering::RegisterNewFragmentShader(material.fragmentShader, _fragShaderIndex);
		}
		
		if (_vertShaderIndex != 0 || _fragShaderIndex != 0)
		{
			Rendering::RegisterNewShaderProgram(_vertShaderIndex, _fragShaderIndex, material.shaderProgramIndex);
		}
		Rendering::DeleteShader(_vertShaderIndex);
		Rendering::DeleteShader(_fragShaderIndex);
		material.compiled = true;
	}
	
	if (material.shaderProgramIndex)
	{
		Rendering::UseShaderProgram(material.shaderProgramIndex);
	}
}

} // Heavenly::World
