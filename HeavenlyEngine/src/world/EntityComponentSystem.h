#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <functional>
#include <string>
#include <typeinfo>
#include <vector>

#include "MathBaseTypes.h"

namespace Heavenly::World
{

struct WorldAdmin;

class Component;

class Entity final
{
public:
	Entity() = delete;
	~Entity() = delete;
	explicit Entity(const WorldAdmin* world, const std::string& id) : world(world), id(id) { }

	inline const WorldAdmin* GetWorld() const { return world; }
	inline std::string GetId() const { return id; }
	inline const std::vector<Component*> GetComponents() const { return components; }

private:
	const WorldAdmin* world = nullptr;
	std::string id;
	std::vector<Component*> components;
};

class Component
{
public:
	explicit Component(const Entity* e) : entity(e) {}
	
	virtual ~Component() = default;

	template <typename Component_t>
	requires std::is_base_of_v<Component, Component_t>
	Component_t* GetSibling() const
	{
		// TODO: Get component on same entity with this type;
		for (auto* _c : entity->GetComponents())
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

struct TransformComponent : public Component
{
	Math::Vector3<float> position = {0, 0, 0};
	Math::Vector3<float> rotation = {0, 0, 0};
	Math::Vector3<float> scale = {0, 0, 0};
};

struct WorldAdmin
{
	using SystemTickFunc = std::function<void(float)>;
	using ComponentInitFunc = std::function<void(Component*)>;

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

WorldAdmin* CreateWorld();

// Entity Functions
Entity* CreateEntity(WorldAdmin* world, const std::string& id);

void DestroyEntity(const int worldID, const unsigned int entity_id);

// Admin lifetime functions
void Tick(WorldAdmin* world, const float deltaTime);

void Terminate();

void RegisterComponentInitFunc(const std::type_info& typeInfo, const std::function<void(Component*)> initFunc);

template<typename Component_t>
Component_t* CreateComponent(Entity* entity)
{
	auto* _world = const_cast<WorldAdmin*>(entity->GetWorld());
	auto* _newComponent = new Component_t(entity);
	_world->components.push_back(_newComponent);
	return _newComponent;
}

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
