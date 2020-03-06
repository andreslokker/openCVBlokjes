#include "ArgumentParser.hpp"
#include "ObjectDetector.hpp"
#include "ColorDetector.hpp"
#include "ShapeDetector.hpp"
#include "Timer.hpp"
#include <chrono>
#include <iostream>

ObjectDetector::ObjectDetector(InputHandler* inputHandler, ArgumentParser* argumentParser) : inputHandler(inputHandler), argumentParser(argumentParser), configure(this) {
    cap.open(webcamId);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    cap.read(image);
    thresholdImage = cv::Mat::zeros(image.size(), CV_8UC3);
    finalImage = cv::Mat::zeros(image.size(), CV_8UC3);
}

ObjectDetector::~ObjectDetector() {

}

void ObjectDetector::start() {
    if(inputHandler->getEnableColorConfig()) {
       configure.startConfiguration();
    }
    configure.readConfiguration();

    if(argumentParser->getMode() == Mode::INTERACTIVE)
        threadPtr = std::make_unique<std::thread>(&ObjectDetector::detectObjects, this);
    else
        threadPtr = std::make_unique<std::thread>(&ObjectDetector::detectBatch, this);   
    threadPtr->detach();
}

cv::Mat& ObjectDetector::getWebcamImage() {
    cap.read(image);
    return image;
}

void ObjectDetector::detectBatch() {
    std::chrono::system_clock::time_point previousMillis = std::chrono::system_clock::now();
    inputHandler->getMutex().lock(); // the input vector with commands gets locked
    while(true) {
        std::chrono::system_clock::time_point millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis-previousMillis;
        if(duration.count() > 1) {
            thresholdImage = cv::Mat::zeros(image.size(), CV_8UC3);
            finalImage = cv::Mat::zeros(image.size(), CV_8UC3);
            for(std::size_t i = 0; i < inputHandler->getInputVector().size(); i++) {
                Timer timer;
                std::pair<std::string, std::string> goal = inputHandler->getInputVector().at(i);
                imageMutex.lock(); // the image variables get locked
                ColorDetector colorDetector;
                thresholdImage = colorDetector.detectColor(image, configure.getColorConfiguration(goal.second), timer);
                ShapeDetector shapeDetector;
                cv::Mat image = shapeDetector.detectShape(thresholdImage, goal.first, timer, argumentParser->getMode());
                cv::add(finalImage, image, finalImage);
                imageMutex.unlock();
            }
            previousMillis = std::chrono::system_clock::now();
        }   
    }
    inputHandler->getMutex().unlock();
}

void ObjectDetector::detectObjects() {
    std::chrono::system_clock::time_point previousMillis = std::chrono::system_clock::now();
    std::size_t currentObject = 0;
    std::pair<std::string, std::string> goal;
    while(true) {
        std::chrono::system_clock::time_point millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis-previousMillis;
        if(duration.count() > 0.2) {
            inputHandler->getMutex().lock();
            if(currentObject < inputHandler->getInputVector().size()) {
                goal = inputHandler->getInputVector().at(currentObject);
            }
            inputHandler->getMutex().unlock();
            if(goal.first != "" && goal.second != "") {
                Timer timer;
                imageMutex.lock(); // the images get locked
                ColorDetector colorDetector;
                thresholdImage = colorDetector.detectColor(image, configure.getColorConfiguration(goal.second), timer);
                ShapeDetector shapeDetector;
                finalImage = shapeDetector.detectShape(thresholdImage, goal.first, timer, argumentParser->getMode());
                imageMutex.unlock();
            }
            previousMillis = std::chrono::system_clock::now();
        }
    }
}

void ObjectDetector::showImages() {
    std::chrono::system_clock::time_point previousMillis = std::chrono::system_clock::now();
    while(true) {
        std::chrono::system_clock::time_point millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis - previousMillis;
        if(duration.count() > 0.03) {
            imageMutex.lock();
            cap.read(image);
            cv::imshow("start image", image);
            cv::imshow("tresholdimage", thresholdImage);
            cv::imshow("image", finalImage);
            imageMutex.unlock();
            previousMillis = std::chrono::system_clock::now();
        }

        char key = (char) cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
}

std::mutex& ObjectDetector::getImageMutex() {
    return imageMutex;
}
