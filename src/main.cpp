#include "Configure.hpp"
#include "ColorDetector.hpp"
#include "ShapeDetector.hpp"
#include <opencv2/videoio.hpp>
#include <iostream>
#include <chrono>

int main() {
    //cv::Mat image = cv::imread(cv::String("pictures/picture2.jpg"));
    cv::Mat image;
    cv::Mat thresholdImage;
    cv::Mat finalImage;
    Configure configure;
    cv::VideoCapture cap;
    int deviceID = 2;
    //int apiID = cv::CAP_ANY;
    cap.open(deviceID);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1000);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,1000);
    cap.read(image);
    image.copyTo(finalImage);
    image.copyTo(thresholdImage);
    //configure.startConfiguration();
    std::chrono::system_clock::time_point previousMillis = std::chrono::system_clock::now();

    while(true) {
        std::chrono::system_clock::time_point millis = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = millis-previousMillis;
        cap.read(image);
        if(duration.count() > 0.250) {
            std::pair<std::string, std::string> goal("square", "red");
            ColorDetector colorDetector;
            thresholdImage = colorDetector.detectColor(image, goal.second);
            ShapeDetector shapeDetector;
            finalImage = shapeDetector.detectShape(thresholdImage, goal.first);
            previousMillis = std::chrono::system_clock::now();
        }

        cv::imshow("start image", image);
        cv::imshow("tresholdimage", thresholdImage);
        cv::imshow("image", finalImage);

        char key = (char) cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    return 0;
}