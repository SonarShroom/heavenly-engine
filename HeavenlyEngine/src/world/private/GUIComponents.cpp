#include "world/GUIComponents.h"

#include "logging/LogManager.h"
#include "graphics/Rendering.h"
#include "world/EntityComponentSystem.h"

namespace Heavenly::World
{

RectComponent::RectComponent(const Entity* e)
	: Component(e)
	, vertexBufferId(Rendering::InitVertexBufferObjects(1)[0])
	, vertexArrayId(Rendering::InitVertexArrayObjects(1)[0]) {}

RectComponent::~RectComponent()
{
	Rendering::DeleteBuffers({vertexBufferId});
	Rendering::DeleteArrays({vertexArrayId});
}

void RectRendererSystem([[maybe_unused]] RectComponent* rectComponent, [[maybe_unused]] const float timeDelta)
{
	if (rectComponent->drawDirty)
	{
		Rendering::BindArray(rectComponent->vertexArrayId);
		const auto _transformPos = rectComponent->GetSibling<TransformComponent>()->position;
		const auto _size = rectComponent->size;
		Rendering::BindBuffer(rectComponent->vertexBufferId);
		std::array<float, 9> _vertexPos =
		{
			_transformPos.x, _transformPos.y, _transformPos.z,
			_transformPos.x, _transformPos.y - _size.y, _transformPos.z,
			_transformPos.x + _size.x, _transformPos.y, _transformPos.z
			// {_transformPos.x + _size.x, _transformPos.y - _size.y, _transformPos.z}
		};
		Rendering::BufferStaticData(sizeof(_vertexPos), _vertexPos.data());
		Rendering::SetVertexAttribute(0, 3, 3 * sizeof(float));
		// rectComponent->drawDirty = false;
	}

	// TODO: Render rect using Rendering module;
	
	Rendering::BindArray(rectComponent->vertexArrayId);
	Rendering::DrawArrays(0, 3);
}

} // Heavenly::World
