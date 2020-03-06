#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <string>

enum Mode {
    NONE,
    INTERACTIVE,
    BATCH
};


class ArgumentParser {
    public:
        ArgumentParser();
        virtual ~ArgumentParser();
        void parseArguments(int argc, char** argv);
        const Mode& getMode() const;
        const std::string& getLocation() const;
    private:
        std::string location;
        Mode mode;
};

#endif