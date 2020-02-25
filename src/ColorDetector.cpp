#include "ColorDetector.hpp"
#include <opencv2/photo.hpp>

ColorDetector::ColorDetector() {

}

ColorDetector::~ColorDetector() {

}

cv::Mat ColorDetector::detectColor(cv::Mat& image, const std::string& color) {
    cv::Mat noiseRemovedImage;
    cv::Mat blurredImage;
    cv::Mat tresholdImage;

    cv::GaussianBlur(image, blurredImage, cv::Size(3, 3), 50);

    cvtColor(blurredImage, blurredImage, cv::COLOR_BGR2HSV);
    // please change this line so that it takes the config values
    cv::inRange(blurredImage, cv::Scalar(0, 96, 0), cv::Scalar(180, 255, 255), tresholdImage);

    cv::erode(tresholdImage, tresholdImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9), cv::Point(-1,-1)));
    cv::dilate(tresholdImage, tresholdImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9), cv::Point(-1,-1)));

    //cv::GaussianBlur(tresholdImage, noiseRemovedImage, cv::Size(5, 5), 50);

    //cv::adaptiveThreshold(tresholdImage, noiseRemovedImage, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, -2);
    return tresholdImage;
}