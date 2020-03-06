#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "ArgumentParser.hpp"
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

class InputHandler {
    public:
        /**
         * @brief Construct a new Input Handler object
         * 
         */
        InputHandler();

        /**
         * @brief Destroy the Input Handler object
         * 
         */
        virtual ~InputHandler();

        /**
         * @brief This function starts the inputHandler
         * 
         */
        void start();

        /**
         * @brief Function which keeps checking for input on a seperate thread
         * 
         */
        void run();

        /**
         * @brief This function will read a batch file
         * 
         * @param filename name of the file to read
         */
        void readFile(const std::string& filename);

        /**
         * @brief Get the Input Vector object
         * 
         * @return std::vector<std::pair<std::string, std::string> >& inputVector
         */
        std::vector<std::pair<std::string, std::string> >& getInputVector();

        /**
         * @brief Get the Mutex object
         * 
         * @return std::mutex& inputVectorMutex
         */
        std::mutex& getMutex();

        bool getEnableColorConfig() const;

    private:
        /**
         * @brief This function parses a single line from the batch file and in case of a object + color
         * it will store the command in the inputVector 
         * @param line 
         */
        void parseLine(const std::string& line);

        /**
         * @brief This function checks the command line for input and calls the parse function
         * 
         */
        void readCommandLine();

        std::vector<std::pair<std::string, std::string> >inputVector;
        std::mutex inputVectorMutex;
        std::unique_ptr<std::thread> threadPtr;
        bool enableColorConfig;
};

#endif
