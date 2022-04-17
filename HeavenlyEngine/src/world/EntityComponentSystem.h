#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <functional>
#include <string>
#include <vector>

#include "MathBaseTypes.h"

namespace Heavenly::World
{

struct WorldAdmin;

class Component;

struct Entity final
{
	Entity() = delete;
	~Entity() = default;

	explicit Entity(const WorldAdmin* world, const std::string& id) : world(world), id(id) { }

	const WorldAdmin* world = nullptr;
	std::string id;
	std::vector<Component*> components;
};

class Component
{
public:
	explicit Component(const Entity* e) : entity(e) {}
	
	virtual ~Component() = default;
	
	inline const Entity* GetEntity() const { return entity; }

	template <typename Component_t>
	requires std::is_base_of_v<Component, Component_t>
	Component_t* GetSibling() const
	{
		// TODO: Get component on same entity with this type;
		for (auto* _c : entity->components)
		{
			auto* _casted = dynamic_cast<Component_t*>(_c);
			if (_casted)
			{
				return _casted;
			}
		}
		return nullptr;
	}

private:
	const Entity* entity = nullptr;
};

struct TransformComponent final : public Component
{
	TransformComponent(Entity* e) : Component(e) { }

	Math::Vector3<float> position = {0, 0, 0};
	Math::Vector3<float> rotation = {0, 0, 0};
	Math::Vector3<float> scale = {0, 0, 0};
};

struct WorldAdmin
{
	using SystemTickFunc = std::function<void(float)>;
	using ComponentInitFunc = std::function<void(Component*)>;

	WorldAdmin() = default;
	~WorldAdmin() = default;

	std::vector<Entity*> entities;
	std::vector<Component*> components;
	std::vector<SystemTickFunc> systems;
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

// Admin lifetime functions
WorldAdmin* CreateWorld();

void DestroyWorld(WorldAdmin* admin);

void Tick(WorldAdmin* world, const float deltaTime);

void Terminate();

// Entity Functions
Entity* CreateEntity(WorldAdmin* world, const std::string& id);

void DestroyEntity(Entity* entity);

template<typename Component_t>
Component_t* GetComponent(Entity* entity)
{
	for (auto* _c : entity->components)
	{
		auto* _casted = dynamic_cast<Component_t*>(_c);
		if (_casted)
		{
			return _casted;
		}
	}
	return nullptr;
}

template<typename Component_t>
Component_t* CreateComponent(Entity* entity)
{
	auto* _world = const_cast<WorldAdmin*>(entity->world);
	auto* _newComponent = new Component_t(entity);
	_world->components.push_back(_newComponent);
	entity->components.push_back(_newComponent);
	return _newComponent;
}

void DestroyComponent(Component* component);

template<typename Component_t>
requires std::is_base_of_v<Component, Component_t>
void RegisterSystem(WorldAdmin* world, void (*systemFunction)(Component_t*, const float))
{
	world->systems.push_back(
		[world, systemFunction](const float deltaTime) -> void
		{
			for (auto* c : world->components)
			{
				auto* _tgtComp = dynamic_cast<Component_t*>(c);
				if (_tgtComp)
				{
					(*systemFunction)(_tgtComp, deltaTime);
				}
			}
		}
	);
}

} // Heavenly::World

#endif //ENTITY_COMPONENT_SYSTEM_H_
