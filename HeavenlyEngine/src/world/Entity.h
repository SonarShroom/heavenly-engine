#pragma once

#include <vector>
#include <string>
#include <functional>

namespace Heavenly::World
{

class Component;
class WorldAdmin;

class Entity final
{
public:
	using ComponentRef = std::reference_wrapper<Component>;

	Entity(const std::string& id) : id(id) {}

	inline const std::string& GetID() const { return id; }

	inline const std::vector<ComponentRef>& GetComponents() const { return components; }

private:
	void AddComponent(Component& comp);
	void RemoveComponent(Component& comp);

	friend class WorldAdmin;

	std::string id;
	std::vector<ComponentRef> components;
};

}