#ifndef EVENT_SYSYEM_H_
#define EVENT_SYSYEM_H_

#include <vector>
#include <functional>

namespace Heavenly
{
    namespace EventSystem
    {
        class Event
        {
            Event() = default;
        };

        class EventManager
        {
        public:
            EventManager() = default;
            ~EventManager();

            template<class Event_t>
            void RegisterEventListener(std::function<void(Event_t&)> listener_callback) {
                static_assert(std::is_base_of_v<Event, Event_t>, "Event type must be derived from Event!");
                event_listeners.push_back(listener_callback);
            }

            void PushEvent(Event* new_event);

            void ProcessEvents();

        private:
            using EventQueue = std::vector<Event*>;
            using EventListeners = std::vector<std::function<void(Event&)>>;

            EventQueue event_buffer;
            EventListeners event_listeners;

            float event_processing_timeout { 5 };
        };
    }
}

#endif //EVENT_SYSYEM_H_