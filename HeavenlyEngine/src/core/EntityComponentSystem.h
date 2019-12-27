#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_


namespace Heavenly
{
    namespace EntityComponentSystem
    {
        typedef void (*SystemTickFunc)(float timeDelta);

        // TODO: Define API for the Entity Component System
        // ECS System API
        // Creates an empty entity
        unsigned int CreateEntity();

        unsigned int CreateEntity();

        void RegisterSystemType(SystemTickFunc tick);

        template<typename Component_t>
        void RegisterComponentType(Component_t newComponent);

        void Tick(float timeDelta);
    }
}

#endif //ENTITY_COMPONENT_SYSTEM_H_