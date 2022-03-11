#include "world/GUIComponents.h"

#include "logging/LogManager.h"
#include "graphics/Rendering.h"
#include "world/EntityComponentSystem.h"

namespace Heavenly::World
{

RectComponent::RectComponent(const Entity* e) : Component(e), vbo(Rendering::InitBuffers(1)[0]) {}

RectComponent::~RectComponent()
{
	Rendering::DeleteBuffers({vbo});
}

void RectRendererSystem(RectComponent* rectComponent, [[maybe_unused]] const float timeDelta)
{
	// TODO: Render rect using Rendering module;
	// const auto* _transform = rectComponent->GetSibling<TransformComponent>();
	HV_LOG_INFO("Ticking rect with dt = {}; Rect component size x: {}", timeDelta, rectComponent->size.x);
}

} // Heavenly::World
