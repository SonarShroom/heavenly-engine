#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <functional>

namespace Heavenly
{

namespace EntityComponentSystem
{

class Component
{
    Component(const unsigned int component_id) : component_id(component_id) { }

    unsigned int component_id = 0;
};

class Entity final
{
public:
    Entity() = default;
    Entity(unsigned int id);
    Entity(unsigned int id, std::initializer_list<unsigned int> component_ids);
    ~Entity() = default;

private:
    unsigned int entity_id {0};
    std::vector<unsigned int> component_id_list;
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

class WorldAdmin
{
public:
    WorldAdmin() = default;
    ~WorldAdmin() = default;

    // Admin lifetime functions
    void Tick(float delta_time);
    void KillAdmin();

    // ECS System API
    unsigned int CreateEntity();
    void DestroyEntity(const unsigned int entity_id);

    template<class Component_t, typename ...Args>
    void CreateComponent(const unsigned int entity_id, const Args... args)
    {
        static_assert(std::is_base_of<Component, Component_t>::value, "Component type must be derived from Component!");
        auto new_component = new Component_t(next_component_id++);
        world_components.push_back(new_component);
    }

    template<typename System_t>
    void RegisterSystem()
    {
        world_systems.push_back(
            [](const float delta_time)
            {
                System_t::Tick(delta_time);
            }
        );
    }

private:

    using SystemTickFunc = std::function<void(float)>;

    std::unordered_map<unsigned int, Entity*> world_entities;
    std::vector<Component*> world_components;
    std::vector<SystemTickFunc> world_systems;

    unsigned int next_entity_id = 0;
    unsigned int next_component_id = 0;
};

}

}

#endif //ENTITY_COMPONENT_SYSTEM_H_
