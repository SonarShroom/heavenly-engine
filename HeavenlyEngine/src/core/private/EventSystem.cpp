#include "EventSystem.h"

#include <iostream>
#include <chrono>

using namespace Heavenly::EventSystem;

void EventManager::PushEvent(Event* new_event)
{
    event_buffer.emplace_back(new_event);
}

void EventManager::ProcessEvents()
{
    auto begin_event_process_time = std::chrono::steady_clock::now();
    auto end_event_process_time = begin_event_process_time;
    auto time_difference { end_event_process_time - begin_event_process_time };
    //TODO: this is ugly, replace with something cleaner.
    const float event_ptocessing_timeout_ns = event_processing_timeout * 1000000;
    int events_processed { 0 };
    while(time_difference.count() < event_ptocessing_timeout_ns)
    {
        // TODO: Process events here.
        end_event_process_time = std::chrono::steady_clock::now();
        time_difference = end_event_process_time - begin_event_process_time;
        events_processed++;
    }
    std::cout << "Time difference = " << time_difference.count() << "; Events processed: " << events_processed << std::endl; 
}