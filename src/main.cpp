#include "Configure.hpp"
#include "ColorDetector.hpp"
#include "ShapeDetector.hpp"
#include "InputHandler.hpp"
#include <opencv2/videoio.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex inputQueueMutex;
cv::Mat image;
cv::Mat thresholdImage;
cv::Mat finalImage;
std::chrono::system_clock::time_point previousMillisShapeDetection = std::chrono::system_clock::now();
std::chrono::system_clock::time_point previousMillisMain = std::chrono::system_clock::now();
std::chrono::system_clock::time_point millis = std::chrono::system_clock::now();

void threadFunc(InputHandler& inputHandler) {
    std::pair<std::string, std::string> goal;
    while(true) {
        millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis-previousMillisShapeDetection;
        if(duration.count() > 1) {
            inputQueueMutex.lock();
            if(inputHandler.getInputQueue().size() >= 1) {
                goal = inputHandler.getInputQueue().front();
                if(inputHandler.getInputQueue().size() > 1)
                    inputHandler.getInputQueue().pop();
            }
            inputQueueMutex.unlock();
            std::cout << "goal: " << goal.first << " " << goal.second << std::endl;
            if(goal.first != "" && goal.second != "") {
                ColorDetector colorDetector;
                thresholdImage = colorDetector.detectColor(image, goal.second);
                ShapeDetector shapeDetector;
                finalImage = shapeDetector.detectShape(thresholdImage, goal.first);
            }
            previousMillisShapeDetection = std::chrono::system_clock::now();
        }
    }
}

int main() {
    Configure configure;
    //configure.startConfiguration();

    InputHandler inputHandler(&inputQueueMutex);
    cv::VideoCapture cap;
    int deviceID = 2;
    cap.open(deviceID);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    cap.read(image);
    image.copyTo(finalImage);
    image.copyTo(thresholdImage);

    std::thread mThread(threadFunc, std::ref(inputHandler));

    while(true) {
        millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis - previousMillisMain;
        if(duration.count() > 0.03) {
            cap.read(image);
            cv::imshow("start image", image);
            cv::imshow("tresholdimage", thresholdImage);
            cv::imshow("image", finalImage);
            previousMillisMain = std::chrono::system_clock::now();
        }

        char key = (char) cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    return 0;
}