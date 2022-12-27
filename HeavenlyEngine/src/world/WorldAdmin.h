#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

namespace Heavenly::World
{

class WorldAdmin
{
public:
	using SystemTickFunc = std::function<void(float)>;
	using ComponentInitFunc = std::function<void(Component&)>;

	void Tick(const float deltaTime);

	Entity& CreateEntity(const std::string& id);
	Entity* GetEntity(const std::string& id);
	void DestroyEntity(const std::string& id);

	inline std::size_t GetNumEntities() { return entities.size(); }

	void IterateWorldEntities(const std::function<void(Entity&)>& visitor);

	template<ComponentType ComponentT, typename ...ArgsT>
	ComponentT* CreateComponent(Entity& entity, ArgsT&&... args) noexcept
	{
		for (auto& _ent : entities)
		{
			if (&_ent != &entity) continue;

			auto _newComponent = std::make_unique<ComponentT>(entity, std::forward<ArgsT>(args)...);
			auto* _newComponentPtr = _newComponent.get();
			_ent.AddComponent(*_newComponent);
			components.push_back(std::move(_newComponent));
			return _newComponentPtr;
		}
		return nullptr;
	}

	template<typename ComponentT>
	requires std::is_base_of_v<Component, ComponentT>
	ComponentT* GetComponent(Entity& entity) const
	{
		for (const auto& ent : entities)
		{
			if (&entity != &ent) continue;

			for (auto& _c : ent.GetComponents())
			{
				auto* _casted = dynamic_cast<ComponentT*>(&_c.get());
				if (_casted) return _casted;
			}
		}
		return nullptr;
	}

	void DestroyComponent(Component& component);

	inline std::size_t GetNumComponents() { return components.size(); }

	inline bool IsComponentRegistered(Component& component) {
		return std::find_if(components.begin(), components.end(), [&component](std::unique_ptr<Component>& c){
			return c.get() == &component;
		}) != components.end();
	}

	template<typename ComponentT>
	requires std::is_base_of_v<Component, ComponentT>
	void RegisterSystem(void (*systemFunction)(ComponentT&, const float))
	{
		systems.push_back([&comps = this->components, systemFunction](const float deltaTime) {
			for (auto& c : comps)
			{
				auto* _tgtComp = dynamic_cast<ComponentT*>(c.get());
				if (_tgtComp)
				{
					(*systemFunction)(*_tgtComp, deltaTime);
				}
			}
		});
	}

	template<class ObjectT, typename ComponentT>
	void RegisterObjectSystem(ObjectT& callObject, void (ObjectT::*method)(ComponentT&, const float))
	{
		systems.emplace_back([&callObject, method, &comps = this->components](const float deltaTime) {
			for (auto& c : comps)
			{
				auto* _tgtComp = dynamic_cast<ComponentT*>(c.get());
				if (_tgtComp)
				{
					(callObject.*method)(*_tgtComp, deltaTime);
				}
			}
		});
	}

private:
	std::vector<Entity> entities;
	std::vector<std::unique_ptr<Component>> components;
	std::vector<SystemTickFunc> systems;
};

}