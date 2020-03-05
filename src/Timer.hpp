#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer {
    public:
        /**
         * @brief Construct a new Timer object
         * 
         */
        Timer();

        /**
         * @brief Destroy the Timer object
         * 
         */
        virtual ~Timer();

        /**
         * @brief This function starts a timer
         * 
         */
        void start();

        /**
         * @brief This function stops a timer
         * 
         */
        void stop();

        /**
         * @brief This function returns a duration between the start moment and end moment
         * 
         * @return std::clock_t duration
         */
        std::clock_t getDuration();
    private:
        std::clock_t startTime;
        std::clock_t endTime;
};

#endif