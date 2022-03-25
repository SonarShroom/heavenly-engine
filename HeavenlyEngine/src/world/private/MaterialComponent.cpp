#include "MaterialComponent.h"

namespace Heavenly::World
{

MaterialComponent::MaterialComponent(Entity* e) : Component(e)
{

}

MaterialComponent::~MaterialComponent()
{

}

void MaterialRendererSystem(MaterialComponent* material, const float deltaTime)
{

}

} // Heavenly::World
