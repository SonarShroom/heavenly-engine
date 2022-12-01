#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "math/MathBaseTypes.h"

namespace Heavenly::World
{

class WorldAdmin;

class Component;

class Entity final
{
public:
	using ComponentRef = std::reference_wrapper<Component>;

	Entity(const WorldAdmin& world, const std::string& id) : world(world), id(id) {}

	inline const std::string& GetID() const { return id; }

	inline const std::vector<ComponentRef>& GetComponents() const { return components; }
	void AddComponent(Component& comp);
	void RemoveComponent(Component& comp);

private:
	const WorldAdmin& world;
	std::string id;
	std::vector<ComponentRef> components;
};

class Component
{
public:
	explicit Component(Entity& e) : entity(e) {}
	
	virtual ~Component() = 0;

	Entity& GetEntity() const { return entity; }

	template <typename Component_t>
	requires std::is_base_of_v<Component, Component_t>
	Component_t* GetSibling() const
	{
		// TODO: Get component on same entity with this type;
		for (auto& _c : entity.GetComponents())
		{
			auto* _casted = dynamic_cast<Component_t*>(&_c.get());
			if (_casted)
				return _casted;
		}
		return nullptr;
	}

private:
	Entity& entity;
};

class TransformComponent final : public Component
{
public:
	TransformComponent(Entity& e) : Component(e) { }

	Math::Vector3<float> position;
	Math::Vector3<float> rotation;
	Math::Vector3<float> scale;
};

class WorldAdmin
{
public:
	using SystemTickFunc = std::function<void(float)>;
	using ComponentInitFunc = std::function<void(Component&)>;

	WorldAdmin();

	void Tick(const float deltaTime);

	Entity& CreateEntity(const std::string& id);
	Entity* GetEntity(const std::string& id);
	void DestroyEntity(const std::string& id);
	
	void IterateWorldEntities(void(*visitor)(Entity&));

	template<typename Component_t, typename ...Args_t>
	requires std::is_base_of_v<Component, Component_t>
	Component_t* CreateComponent(Entity& entity, Args_t... args)
	{
		for (auto& ent : entities)
		{
			if (&entity != &ent) continue;

			auto _newComponent = std::make_unique<Component_t>(entity, args...);
			auto* _newComponentPtr = _newComponent.get();
			ent.AddComponent(*_newComponent);
			components.push_back(std::move(_newComponent));
			return _newComponentPtr;
		}
		return nullptr;
	}

	template<typename Component_t>
	requires std::is_base_of_v<Component, Component_t>
	Component_t* GetComponent(Entity& entity) const
	{
		for (const auto& ent: entities)
		{
			if (&entity != &ent) continue;

			for (auto& _c : ent.GetComponents())
			{
				auto* _casted = dynamic_cast<Component_t*>(&_c);
				if (_casted) return _casted;
			}
		}
		return nullptr;
	}

	void DestroyComponent(Component& component);

	template<typename Component_t>
	requires std::is_base_of_v<Component, Component_t>
	void RegisterSystem(void (*systemFunction)(Component_t&, const float))
	{
		systems.push_back(
			[&comps = this->components, systemFunction](const float deltaTime) -> void
			{
				for (auto& c : comps)
				{
					auto* _tgtComp = dynamic_cast<Component_t*>(c.get());
					if (_tgtComp)
					{
						(*systemFunction)(*_tgtComp, deltaTime);
					}
				}
			}
		);
	}

private:
	std::vector<Entity> entities;
	std::vector<std::unique_ptr<Component>> components;
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

} // Heavenly::World
