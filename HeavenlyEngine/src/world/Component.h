#pragma once

#include "HeavenlyMath.h"

#include "world/Entity.h"

namespace Heavenly::World
{

class Component
{
public:
	explicit Component(Entity& e) : entity(e) {}

	virtual ~Component() = default;

	Entity& GetEntity() const { return entity; }

	template <typename ComponentT>
	requires std::is_base_of_v<Component, ComponentT>
	ComponentT* GetSibling() const
	{
		// TODO: Get component on same entity with this type;
		for (auto& _c : entity.GetComponents())
		{
			auto* _casted = dynamic_cast<ComponentT*>(&_c.get());
			if (_casted)
				return _casted;
		}
		return nullptr;
	}

private:
	Entity& entity;
};

template<typename ComponentT>
concept ComponentType = std::is_base_of_v<Component, ComponentT>;

class TransformComponent final : public Component
{
public:
	TransformComponent(Entity& e) : Component(e) { }

	glm::vec3 position = {0.f, 0.f, 0.f};
	glm::vec3 rotation = {0.f, 0.f, 0.f};
	glm::vec2 scale = {1.f, 1.f};
};

/*template <typename Vector_t, class Component_t>
class ComponentIterator
{
private:
	Vector_t& vector;
	Component_t* current = nullptr;

public:
	ComponentIterator(const Vector_t& vector) : vector(vector)
	{
		for ()
		{

		}
	}

	void operator *() const
	{

	}
};
*/
}