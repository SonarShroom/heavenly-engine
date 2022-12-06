#pragma once

#include <string>

#include "Component.h"

namespace Heavenly::World
{

struct MaterialComponent : public Component
{
	MaterialComponent(Entity& e) : Component(e) { }
	~MaterialComponent() = default;

	bool compiled = false;
	unsigned int shaderProgramIndex = 0;

	// TODO: For now these are changed at will inside the main loop, but they should be initialized by a specific function most likely.
	std::string vertexShader;
	std::string fragmentShader;
};

void MaterialRendererSystem(MaterialComponent& material, const float deltaTime);

} // Heavenly::World

