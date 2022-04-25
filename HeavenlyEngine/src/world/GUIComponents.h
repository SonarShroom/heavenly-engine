#pragma once

#include "graphics/RenderPrimitives.h"
#include "world/EntityComponentSystem.h"

#include "math/MathBaseTypes.h"

namespace Heavenly::World
{

struct RectComponent : public Component
{
	RectComponent(const Entity* e) : Component(e) {}
	
	~RectComponent() = default;

	Math::Vector2<float> size = {};
	Math::Vector4<float> color = {};

	bool drawDirty = true;
	Rendering::Quad quad = {};
};

void RectRendererSystem(RectComponent* rectComponent, [[maybe_unused]] const float timeDelta);

} // Heavenly::World