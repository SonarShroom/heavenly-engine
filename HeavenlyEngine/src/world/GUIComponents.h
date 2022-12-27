#pragma once

#include "world/Component.h"

#include "graphics/RenderPrimitives.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Heavenly::World
{

struct RectComponent : public Component
{
	RectComponent(Entity& e) : Component(e) {}
	
	~RectComponent() = default;

	bool drawDirty = true;

	glm::vec2 size = {0.f, 0.f};
	glm::vec4 color = {0.f, 0.f, 0.f, 0.f};
	Graphics::Quad quad;
};

} // Heavenly::World