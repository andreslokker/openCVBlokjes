#include "ArgumentParser.hpp"
#include "Configure.hpp"
#include "ObjectDetector.hpp"
#include "InputHandler.hpp"

int main(int argc, char** argv) {
    ArgumentParser argumentParser;
    argumentParser.parseArguments(argc, argv);
    InputHandler inputHandler(&argumentParser);
    ObjectDetector objectDetector(&inputHandler, &argumentParser);
    
    Configure configure(&objectDetector);
    //configure.startConfiguration();

    inputHandler.start();
    objectDetector.start();
    objectDetector.showImages();

    return 0;
}