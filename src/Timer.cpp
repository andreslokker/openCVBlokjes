#include "Timer.hpp"

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::start() {
    startTime = std::clock();
}

void Timer::stop() {
    endTime = std::clock();
}

std::clock_t Timer::getDuration() const {
    return endTime - startTime;
}