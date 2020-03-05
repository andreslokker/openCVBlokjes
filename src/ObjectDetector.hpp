#ifndef OBJECTDETECTOR_HPP
#define OBJECTDETECTOR_HPP

#include "InputHandler.hpp"
#include "Configure.hpp"
#include <opencv2/videoio.hpp>
#include <memory>
#include <thread>
#include <mutex>

class ObjectDetector {
    public:
        /**
         * @brief Construct a new Object Detector object
         * 
         * @param inputHandler A inputHandler which contains the tasks which needs to be executed.
         * @param argumentParser A argument parser which did parse arguments given to the application
         */
        ObjectDetector(InputHandler* inputHandler, ArgumentParser* argumentParser);

        /**
         * @brief Destroy the Object Detector object
         * 
         */
        virtual ~ObjectDetector();

        /**
         * @brief Get the Webcam Image object
         * 
         * @return cv::Mat& webcam image
         */
        cv::Mat& getWebcamImage();

        /**
         * @brief This function will start the object detector based on the mode in the Argument Parser class
         * 
         */
        void start();

        /**
         * @brief This function will detect objects based on objects which are given in the batch file.
         * It will only run once
         */
        void detectBatch();

        /**
         * @brief This function will detect objects based on objects which are given in the terminal. It will keep running
         * until the command "exit"
         */
        void detectObjects();

        /**
         * @brief This function opens the webcam, color detection and shape detection OpenCV windows
         * 
         */
        void showImages();
    private:
        const int webcamId = 2;
        cv::VideoCapture cap;
        cv::Mat image;
        cv::Mat thresholdImage;
        cv::Mat finalImage;
        InputHandler* inputHandler;
        ArgumentParser* argumentParser;
        Configure configure;
        std::unique_ptr<std::thread> threadPtr;
        std::mutex imageMutex;
};

#endif
