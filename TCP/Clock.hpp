#pragma once
#include "DataTypes.hpp"
#include <mutex>
#include <thread>

class Clock {
    public:
        Clock();
        void Tick();
        int GetSequenceNumber();
    private:
        int four_microseconds_timer = 1;
        std::thread tick_thread;
        std::mutex timer_mutex;

};