#ifndef EVENT_SYSYEM_H_
#define EVENT_SYSYEM_H_

#include "EntityComponentSystem.h"

#include <vector>

namespace Heavenly
{
    namespace EventSystem
    {
        class Event : public EntityComponentSystem::Component
        {

        };

        class EventManager
        {
        public:
            template<class Event_t>
            void PushEvent()
            {
                static_assert(std::is_base_of_v<Event, Event_t>, "Event type must be derived from Event!");
                auto new_event = new Event_t();
                event_buffer.emplace_back(new_event);
            }

        private:
            std::vector<Event*> event_buffer;
        };
    }
}

#endif //EVENT_SYSYEM_H_