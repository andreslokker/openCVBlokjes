#ifndef OBJECTDETECTOR_HPP
#define OBJECTDETECTOR_HPP

#include "InputHandler.hpp"
#include <opencv2/videoio.hpp>
#include <memory>
#include <thread>
#include <mutex>

class ObjectDetector {
    public:
        ObjectDetector(InputHandler* inputHandler, ArgumentParser* argumentParser);
        virtual ~ObjectDetector();

        cv::Mat& getWebcamImage();
        void start();
        void detectBatch();
        void detectObjects();
        void showImages();
    private:
        const int webcamId = 2;
        cv::VideoCapture cap;
        cv::Mat image;
        cv::Mat thresholdImage;
        cv::Mat finalImage;
        InputHandler* inputHandler;
        ArgumentParser* argumentParser;
        std::unique_ptr<std::thread> threadPtr;
};

#endif