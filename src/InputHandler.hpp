#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <queue>
#include <string>
#include <thread>
#include <mutex>

class InputHandler {
    public:
        InputHandler(std::mutex* inputQueueMutex);
        virtual ~InputHandler();
        void run();
        std::queue<std::pair<std::string, std::string> >& getInputQueue();
	void setMode(const std::string& mode);
	void setInputFile(const std::string& inputFile);

    private:
        void parseLine(const std::string& line);
        void readFile(const std::string& filename);
        void readCommandLine();
        std::queue<std::pair<std::string, std::string> >inputQueue;
        std::mutex* inputQueueMutex;
        std::thread thread1;
        std::string mode;
        std::string inputFile;
};

#endif
