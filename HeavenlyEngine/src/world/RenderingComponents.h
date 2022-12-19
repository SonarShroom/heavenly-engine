#pragma once

#include <string>

#include "Component.h"

namespace Heavenly::Resources
{
class Shader;
}

namespace Heavenly::World
{

struct MaterialComponent : public Component
{
	MaterialComponent(Entity& e) : Component(e) { }
	MaterialComponent(Entity& e, Resources::Shader& s) : Component(e), shader(&s) { }

	Resources::Shader* shader = nullptr;
};

} // Heavenly::World

