#include "ArgumentParser.hpp"
#include <cstring>

ArgumentParser::ArgumentParser() : mode(Mode::NONE) {

}

ArgumentParser::~ArgumentParser() {

}

void ArgumentParser::parseArguments(int argc, char** argv) {
    if(argc >= 3 && strcmp(argv[1], "-batch") == 0) {
        mode = Mode::BATCH;
        location = argv[2];
    } else {
        mode = Mode::INTERACTIVE;
    }
}

const Mode& ArgumentParser::getMode() const {
    return mode;
}

const std::string& ArgumentParser::getLocation() const {
    return location;
}