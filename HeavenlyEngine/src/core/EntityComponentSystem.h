#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

#include <vector>
#include <initializer_list>

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
            void Tick(float deltaTime);
        };

        class Entity
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

        class EntityAdmin;

        // TODO: Define API for the Entity Component System
        // ECS System API
        // Creates an empty entity
        unsigned int CreateEntity();

        unsigned int CreateEntity();

        void RegisterSystemType(EntityAdmin* targetAdmin, System system);

        template<typename Component_t>
        void RegisterComponentType(Component_t newComponent);

        void Tick(EntityAdmin* targetAdmin, float timeDelta);
    }
}

#endif //ENTITY_COMPONENT_SYSTEM_H_