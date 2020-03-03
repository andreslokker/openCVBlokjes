#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer {
    public:
        Timer();
        virtual ~Timer();
        void start();
        void stop();
        std::clock_t getDuration();
    private:
        std::clock_t startTime;
        std::clock_t endTime;
};

#endif