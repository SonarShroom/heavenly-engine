#ifndef ENTITY_COMPONENT_SYSTEM_H_
#define ENTITY_COMPONENT_SYSTEM_H_

namespace Heavenly
{
	namespace EntityComponentSystem
	{
		// TODO: Define API for the Entity Component System
		template<typename Entity_t, typename ...Component_t>
		void RegisterEntityType(Entity_t newEntityType, Component_t ...componentsList);

		template<typename System_t>
		void RegisterSystemType(System_t newSystem);

		template<typename Component_t>
		void RegisterComponentType(Component_t newComponent);
	}
}

#endif //ENTITY_COMPONENT_SYSTEM_H_