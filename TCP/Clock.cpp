#include "Clock.hpp"
#include <iostream>

void Clock::Tick() {
    /*for(;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        {
            std::lock_guard<std::mutex>  lock(timer_mutex);
            ++four_microseconds_timer;
        }
    }*/
}

Clock::Clock() {
    //tick_thread = std::thread(&Clock::Tick, this);
}

int Clock::GetSequenceNumber() {
    return four_microseconds_timer;
   // return 1;
}