#ifndef GUI_H_
#define GUI_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"
#include <string>

namespace Heavenly
{
    namespace GUI
    {
        class GUIComponent : public EntityComponentSystem::Component
        {
        public:
            GUIComponent() = default;
            Math::Vector2 position;
            Math::Vector2 size;
        };

        class GUISystem : public EntityComponentSystem::System
        {
        public:
            void Tick(float time_delta) override;
        };
    }
}

#endif //GUI_H_