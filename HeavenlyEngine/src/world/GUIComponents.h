#pragma once

#include "world/EntityComponentSystem.h"

#include "math/MathBaseTypes.h"

namespace Heavenly::World
{

struct RectComponent : public Component
{
	RectComponent(const Entity* e);
	
	~RectComponent();

	Math::Vector2<float> size;
	Math::Vector4<float> color;
	
	bool drawDirty = true;
	
	const unsigned int vertexBufferId = 0;
	const unsigned int vertexArrayId = 0;
};

void RectRendererSystem(RectComponent* rectComponent, [[maybe_unused]] const float timeDelta);

} // Heavenly::World