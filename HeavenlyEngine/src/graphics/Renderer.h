#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "math/MathBaseTypes.h"
#include "BatchRendering.hpp"
#include "RenderPrimitives.h"

namespace Heavenly::World
{
	struct RectComponent;
	struct MaterialComponent;
}

namespace Heavenly::Resources
{
	class Shader;
}

namespace Heavenly::Graphics
{

class Renderer
{
public:
	Renderer(const int viewportWidth, const int viewportHeight);
	Renderer(const Math::Vector2& viewportSize) : Renderer((int)viewportSize.x, (int)viewportSize.y) {}
	~Renderer();

	void Tick(const float deltaTime);

	void RectRendererSystem(World::RectComponent& rectComponent, [[maybe_unused]] const float timeDelta);

	void MaterialRendererSystem(World::MaterialComponent& material, const float deltaTime);

private:

	void EmitTriangleCommand(const Triangle* triangle);

	void EmitQuadCommand(const Quad* quad);

	void EmitUseShaderCommand(const Resources::Shader& shader);

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;

	std::vector<RenderCommand> renderCommands;
};

}
