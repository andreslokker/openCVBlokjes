#include "ColorDetector.hpp"

ColorDetector::ColorDetector() {

}

ColorDetector::~ColorDetector() {

}

cv::Mat ColorDetector::detectColor(cv::Mat& image, const std::string& color) {
    cv::Mat blurredImage;
    cv::Mat tresholdImage;
    
    cv::GaussianBlur(image, blurredImage, cv::Size(9,9), 100);
    cvtColor(blurredImage, blurredImage, cv::COLOR_BGR2HSV);

    // please change this line so that it takes the config values
    cv::inRange(blurredImage, cv::Scalar(0, 0, 0), cv::Scalar(5, 255, 255), tresholdImage);
    cv::erode(tresholdImage, tresholdImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9), cv::Point(-1,-1)));
    cv::dilate(tresholdImage, tresholdImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9), cv::Point(-1,-1)));
    return tresholdImage;
}