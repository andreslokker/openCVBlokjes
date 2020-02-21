#include "ShapeDetector.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define SQUARE_MARGE_PIXELS 5

ShapeDetector::ShapeDetector() {

}

ShapeDetector::~ShapeDetector() {

}

bool ShapeDetector::isCircle(std::vector<cv::Point>& approx) {
    
}

bool ShapeDetector::isSquare(std::vector<cv::Point>& approx) {
    if(approx.size() >= 4) {
        std::vector<double> foundValues;
        for(int i = 0; i < approx.size(); i++) {
            for(int y = i+1; y < approx.size(); y++) {
                foundValues.push_back(cv::norm(cv::Mat(approx.at(i)), cv::Mat(approx.at(y))));
            }
        }

        for(int y = 0; y < foundValues.size(); y++) {
            int nrOfMatchingLength = 0;
            for(int q = 0; q < foundValues.size(); q++) {
                int lineDistance = ceil(foundValues.at(q) - foundValues.at(y));
                if(lineDistance >= (-1 * SQUARE_MARGE_PIXELS) && lineDistance <= SQUARE_MARGE_PIXELS) {
                    nrOfMatchingLength++;
                }
            }
            if(nrOfMatchingLength >= 4) {
                return true;
            }
        }
    }
    return false;
}

cv::Mat ShapeDetector::detectShape(cv::Mat& image, const std::string& typeOfShape) {
    std::vector<std::vector<cv::Point>> imgCountours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat imageContours = cv::Mat::zeros( image.size(), CV_8UC3 );
    cv::RNG rng(12345);

    findContours(image, imgCountours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    for(int i = 0; i < imgCountours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(imgCountours.at(i)), approx, cv::arcLength(cv::Mat(imgCountours.at(i)), true)*0.02, true);

        if(std::fabs(cv::contourArea(imgCountours.at(i)) >= 100) && 
        isContourConvex(approx)) {
            std::cout << approx.size() << std::endl;
            if((approx.size() == 3 && typeOfShape == "triangle") ||
            ((approx.size() >= 4 && approx.size() <= 6) && (typeOfShape == "square" && (isSquare(approx)) || (typeOfShape == "rectangle" && !isSquare(approx)))) ||
            (approx.size() > 6)) { // circle or semi circel 
                cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                drawContours(imageContours, imgCountours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
            }
        }
    }

    return imageContours;
}