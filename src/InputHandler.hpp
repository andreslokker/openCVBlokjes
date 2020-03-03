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
        InputHandler();
        virtual ~InputHandler();
        void start();
        void run();
        void readFile(const std::string& filename);
        std::vector<std::pair<std::string, std::string> >& getInputVector();
        std::mutex& getMutex();
    private:
        void parseLine(const std::string& line);
        void readCommandLine();

        std::vector<std::pair<std::string, std::string> >inputVector;
        std::mutex inputVectorMutex;
        std::unique_ptr<std::thread> threadPtr;
};

#endif
