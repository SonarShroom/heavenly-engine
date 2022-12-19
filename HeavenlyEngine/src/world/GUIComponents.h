#pragma once

#include "world/Component.h"

#include "graphics/RenderPrimitives.h"
#include "math/MathBaseTypes.h"

namespace Heavenly::World
{

struct RectComponent : public Component
{
	RectComponent(Entity& e) : Component(e) {}
	
	~RectComponent() = default;

	bool drawDirty = true;

	Math::Vector2 size;
	Math::Vector4 color;
	Graphics::Quad quad;
};

} // Heavenly::World