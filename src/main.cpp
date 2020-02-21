#include "Configure.hpp"
#include "ColorDetector.hpp"
#include "ShapeDetector.hpp"
#include <iostream>

int main() {
    cv::Mat image = cv::imread(cv::String("pictures/picture2.jpg"));
    Configure configure;
    //configure.startConfiguration();
    std::pair<std::string, std::string> goal("square", "red");
    ColorDetector colorDetector;
    cv::Mat thresholdImage = colorDetector.detectColor(image, goal.second);
    ShapeDetector shapeDetector;
    cv::Mat finalImage = shapeDetector.detectShape(thresholdImage, goal.first);

    while(true) {
        cv::imshow("start image", image);
        cv::imshow("image", finalImage);

        char key = (char) cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    return 0;
}