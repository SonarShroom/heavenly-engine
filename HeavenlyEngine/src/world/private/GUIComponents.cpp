#include "world/GUIComponents.h"

#include "logging/LogManager.h"
#include "graphics/Rendering.h"

namespace Heavenly::World
{

void RectRendererSystem(RectComponent& rectComponent, [[maybe_unused]] const float timeDelta)
{
	if (rectComponent.drawDirty)
	{
		const auto _transformPos = rectComponent.GetSibling<TransformComponent>()->position;
		const auto _size = rectComponent.size;
		rectComponent.quad.verts[0] = { 
			{_transformPos.x, _transformPos.y, _transformPos.z},
			rectComponent.color
		};
		rectComponent.quad.verts[1] = { 
			{_transformPos.x, _transformPos.y - _size.y, _transformPos.z},
			rectComponent.color
		};
		rectComponent.quad.verts[2] = { 
			{_transformPos.x + _size.x, _transformPos.y, _transformPos.z},
			rectComponent.color
		};
		rectComponent.quad.verts[3] = { 
			{_transformPos.x + _size.x, _transformPos.y - _size.y, _transformPos.z},
			rectComponent.color
		};
		rectComponent.drawDirty = false;
	}

	Rendering::EmitQuadCommand(&rectComponent.quad);
}

} // Heavenly::World
