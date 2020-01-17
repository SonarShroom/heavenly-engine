#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <vector>
#include <initializer_list>
#include <unordered_map>

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

            // ECS System API
            void Tick(float delta_time);

            unsigned int CreateEntity();
            void RegisterComponent(Component* component);
            void RegisterSystem(System* system);

        private:
            std::unordered_map<unsigned int, Entity*> world_entities;
            std::vector<Component*> world_components;
            std::vector<System*> world_systems;

            unsigned int next_entity_id {0};
        };
    }
}

#endif //ENTITY_COMPONENT_SYSTEM_H_