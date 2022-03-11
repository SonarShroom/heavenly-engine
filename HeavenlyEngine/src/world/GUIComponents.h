#pragma once

#include "world/EntityComponentSystem.h"

#include "math/MathBaseTypes.h"

namespace Heavenly::World
{

struct RectComponent : public Component
{
	RectComponent(const Entity* e);
	
	~RectComponent();

	Math::Vector2<int> size;
	Math::Vector4<int> color;
	
	const unsigned int vbo = 0;
};

void RectRendererSystem(RectComponent* rectComponent, [[maybe_unused]] const float timeDelta);

} // Heavenly::World