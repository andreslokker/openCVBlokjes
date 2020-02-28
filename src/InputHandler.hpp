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
        InputHandler(ArgumentParser* argumentParser);
        virtual ~InputHandler();
        void start();
        void run();
        std::vector<std::pair<std::string, std::string> >& getInputVector();
        std::mutex& getMutex();
        bool getFinishedFileReading();
    private:
        void parseLine(const std::string& line);
        void readFile(const std::string& filename);
        void readCommandLine();

        bool finishedFileReading = false;
        ArgumentParser* argumentParser;
        std::vector<std::pair<std::string, std::string> >inputVector;
        std::mutex inputVectorMutex;
        std::unique_ptr<std::thread> threadPtr;
};

#endif