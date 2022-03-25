#pragma once

#include "EntityComponentSystem.h"

namespace Heavenly::World
{

struct MaterialComponent : public Component
{
	MaterialComponent(Entity* e);
	~MaterialComponent();


};

void MaterialRendererSystem(MaterialComponent* material, const float deltaTime);

} // Heavenly::World

