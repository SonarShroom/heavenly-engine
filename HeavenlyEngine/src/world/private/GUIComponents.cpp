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
	if (!rectComponent->drawDirty)
	{
		const auto _transformPos = rectComponent->GetSibling<TransformComponent>()->position;
		const auto _size = rectComponent->size;
		Rendering::BindBuffer(rectComponent->vbo);
		std::array<Math::Vector3<float>, 4> _vertexPos =
		{
			_transformPos,
			{_transformPos.x, _transformPos.y + _size.y, _transformPos.z},
			{_transformPos.x + _size.x, _transformPos.y, _transformPos.z},
			{_transformPos.x + _size.x, _transformPos.y + _size.y, _transformPos.z}
		};
		Rendering::BufferStaticData(sizeof(Math::Vector3<float>) * 4, _vertexPos.data());
		rectComponent->drawDirty = false;
		return;
	}

	glUseProgram(renderable->shader_program_id);
	glBindVertexArray(renderable->vertex_array_object_id);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// TODO: Render rect using Rendering module;

	glBindVertexArray(vertex_array_object_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_id);
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	
}

} // Heavenly::World
