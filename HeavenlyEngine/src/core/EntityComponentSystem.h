#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <vector>
#include <initializer_list>
#include <unordered_map>
#include <type_traits>

namespace Heavenly
{
    namespace EntityComponentSystem
    {
        class Component
        {
        public:
            Component() = default;
            ~Component() = default;
        };

        class System
        {
        public:
            virtual void Tick(float delta_time) = 0;
        };

        class Entity final
        {
        public:
            Entity() = default;
            Entity(unsigned int id);
            Entity(unsigned int id, std::initializer_list<Component*> component_list);
            ~Entity();

        private:
            unsigned int entityID {0};
            std::vector<Component*> components;
        };

        class WorldAdmin
        {
        public:
            WorldAdmin() = default;
            ~WorldAdmin() = default;

            // Admin lifetime functions
            int Init();
            void Tick(float delta_time);
            void KillAdmin();

            // ECS System API
            unsigned int CreateEntity();

            template<class Component_t>
            void CreateComponent()
            {
                static_assert(std::is_base_of_v<Component, Component_t>,
                    "Component type must be derived from Component!");
                auto new_component = new Component_t();
                world_components.push_back(new_component);
            }

            template<class System_t>
            void CreateSystem()
            {
                static_assert(std::is_base_of_v<System, System_t>, "System type must be derived from System!");
                auto new_system = new System_t();
                world_systems.push_back(new_system);
            }

        private:
            std::unordered_map<unsigned int, Entity*> world_entities;
            std::vector<Component*> world_components;
            std::vector<System*> world_systems;

            unsigned int next_entity_id {0};
        };
    }
}

#endif //ENTITY_COMPONENT_SYSTEM_H_