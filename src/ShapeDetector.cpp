#include "ShapeDetector.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define SQUARE_MARGE_PIXELS 30
#define CIRCLE_MARGE_PIXELS 30
#define DOT_MARGE 0.1

ShapeDetector::ShapeDetector() {

}

ShapeDetector::~ShapeDetector() {

}

bool ShapeDetector::isCircle(std::vector<cv::Point>& approx, std::vector<cv::Vec3f>& circles) {
    for(int i = 0; i < circles.size(); i++) {
        bool match = true;
        for(int y = 0; y < approx.size(); y++) {
            // we check if all points are in the circle
            if(!(((approx.at(y).x - circles.at(i)[0]) * (approx.at(y).x - circles.at(i)[0])) +  
            ((approx.at(y).y - circles.at(i)[1]) * (approx.at(y).y - circles.at(i)[1])) 
            < (circles.at(i)[2] * circles.at(i)[2] + CIRCLE_MARGE_PIXELS))) {
                match = false;
            }
        }
        if(match) {
            return true;
        }
    }
    return false;
}

bool ShapeDetector::isRectangularShape(std::vector<cv::Point>& approx) {
    int nrOf90DegreesAngles = 0;
    if(approx.size() >= 4) {
        int nextPoint = 1;
        for(int i = 0; i < approx.size(); i++) {
            cv::Vec2f vector1(approx.at(nextPoint).x - approx.at(i).x, approx.at(nextPoint).y - approx.at(i).y);
            for(int y = 0; y < approx.size(); y++) {
                if(y != nextPoint && i != y) {
                    cv::Vec2f vector2(approx.at(y).x - approx.at(i).x, approx.at(y).y - approx.at(i).y);
                    double dot = ((vector1[0] * vector2[0]) + (vector1[1] * vector2[1])) / (sqrt(pow(vector1[0], 2) + pow(vector1[1], 2)) * sqrt(pow(vector2[0], 2) + pow(vector2[1], 2)));
                    if((dot >= 0 && dot - DOT_MARGE <= 0) ||(dot <= 0 && dot + DOT_MARGE >= 0)) {
                        nrOf90DegreesAngles += 1;
                    }
                }
            }
            if(nextPoint >= approx.size()-1) {
                nextPoint = 0;
            } else {
                nextPoint++;
            }
        }
    }
    return nrOf90DegreesAngles >= 4;
}

bool ShapeDetector::isSquare(std::vector<cv::Point>& approx) {
    if(approx.size() >= 4) {
        std::vector<double> foundValues;
        for(int i = 0; i < approx.size(); i++) {
            for(int y = i+1; y < approx.size(); y++) {
                foundValues.push_back(cv::norm(cv::Mat(approx.at(i)), cv::Mat(approx.at(y))));
            }
        }

        for (int k = 0; k < 2; k++) {
            int posToRemove = 0;
            for(int i = 0; i < foundValues.size(); i++) {
                if(foundValues.at(i) > foundValues.at(posToRemove))
                    posToRemove = i;
            }
            foundValues.erase(foundValues.begin() + posToRemove);
        }

        for(int y = 0; y < foundValues.size(); y++) {
            int nrOfMatchingLength = 0;
            for(int q = 0; q < foundValues.size(); q++) {
                if(q != y) {
                    int lineDistance = ceil(foundValues.at(q) - foundValues.at(y));
                    if(lineDistance >= (-1 * SQUARE_MARGE_PIXELS) && lineDistance <= SQUARE_MARGE_PIXELS) {
                        nrOfMatchingLength++;
                    }
                }
            }
            if(nrOfMatchingLength >= 3) {
                return true;
            }
        }
    }
    return false;
}

cv::Mat ShapeDetector::detectShape(cv::Mat& image, const std::string& typeOfShape) {
    std::vector<std::vector<cv::Point>> imgCountours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Vec3f> circles;
    cv::Mat imageContours = cv::Mat::zeros(image.size(), CV_8UC3);
    cv::RNG rng(12345);

    HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, 50, 35, 10, 100, 400);

    findContours(image, imgCountours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    for(int i = 0; i < imgCountours.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(imgCountours.at(i)), approx, cv::arcLength(cv::Mat(imgCountours.at(i)), true)*0.02, true);

        if(std::fabs(cv::contourArea(imgCountours.at(i)) >= 100) && 
        isContourConvex(approx)) {
            if((approx.size() == 3 && typeOfShape == "triangle") ||
            ((approx.size() >= 4 && approx.size() <= 6) &&
                ((typeOfShape == "square" && isSquare(approx) && isRectangularShape(approx)) ||
                (typeOfShape == "rectangle" && !isSquare(approx) && isRectangularShape(approx)) ||
                (typeOfShape == "semiCircle" && isCircle(approx, circles) && !isRectangularShape(approx)))) ||
            (approx.size() > 6 && isCircle(approx, circles) && typeOfShape == "circle")) { // circle or semi circel 
                cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                drawContours(imageContours, imgCountours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
            }
        }
    }

    return imageContours;
}