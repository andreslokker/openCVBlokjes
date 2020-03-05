#include "ShapeDetector.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define SQUARE_MARGE_PIXELS 30
#define CIRCLE_MARGE_PIXELS 10
#define DOT_MARGE 0.1

ShapeDetector::ShapeDetector() {

}

ShapeDetector::~ShapeDetector() {

}

bool ShapeDetector::isCircle(std::vector<cv::Point>& approx, std::vector<cv::Vec3f>& circles) {
    for(std::size_t i = 0; i < circles.size(); i++) {
        for(std::size_t y = 0; y < approx.size(); y++) {
            for(std::size_t z = 0; z < approx.size(); z++) {
                if(y != z && circles.at(i)[0] >= (float) approx.at(y).x + CIRCLE_MARGE_PIXELS && circles.at(i)[0] <= (float) approx.at(z).x + CIRCLE_MARGE_PIXELS &&
                   circles.at(i)[1] >= (float) approx.at(y).y + CIRCLE_MARGE_PIXELS && circles.at(i)[1] <= (float) approx.at(z).y + CIRCLE_MARGE_PIXELS) {
                       return true;
                   }
            }
        }
    }

    return false;
}

bool ShapeDetector::isRectangularShape(std::vector<cv::Point>& approx) {
    int nrOf90DegreesAngles = 0;
    if(approx.size() >= 4) {
        std::size_t nextPoint = 1;
        for(std::size_t i = 0; i < approx.size(); i++) {
            cv::Vec2f vector1((float) (approx.at(nextPoint).x - approx.at(i).x), (float) (approx.at(nextPoint).y - approx.at(i).y));
            for(std::size_t y = 0; y < approx.size(); y++) {
                if(y != nextPoint && i != y) {
                    cv::Vec2f vector2((float) (approx.at(y).x - approx.at(i).x), (float) (approx.at(y).y - approx.at(i).y));
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
        for(std::size_t i = 0; i < approx.size(); i++) {
            for(std::size_t y = i+1; y < approx.size(); y++) {
                foundValues.push_back(cv::norm(cv::Mat(approx.at(i)), cv::Mat(approx.at(y))));
            }
        }

        for (int k = 0; k < 2; k++) {
            std::size_t posToRemove = 0;
            for(std::size_t i = 0; i < foundValues.size(); i++) {
                if(foundValues.at(i) > foundValues.at(posToRemove))
                    posToRemove = i;
            }
            foundValues.erase(foundValues.begin() + posToRemove);
        }

        for(std::size_t y = 0; y < foundValues.size(); y++) {
            int nrOfMatchingLength = 0;
            for(std::size_t q = 0; q < foundValues.size(); q++) {
                if(q != y) {
                    double lineDistance = ceil(foundValues.at(q) - foundValues.at(y));
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

cv::Mat ShapeDetector::detectShape(cv::Mat& image, const std::string& typeOfShape, Timer& timer, Mode mode) {
    bool found = false;
    std::vector<std::vector<cv::Point>> imgContours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Vec3f> circles;
    cv::Mat imageContours = cv::Mat::zeros(image.size(), CV_8UC3);
    cv::RNG rng(12345);
    HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, 50, 50, 30, 20, 500);

    findContours(image, imgContours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    std::vector<cv::Moments> mu(imgContours.size());
    for(unsigned short i = 0; i < imgContours.size(); i++)
    {
    	mu[i] = moments(imgContours[i], false);
    }

    std::vector<cv::Point2f> mc(imgContours.size());

    for(std::size_t i = 0; i < imgContours.size(); i++) {
    	float cX = (float) (mu[i].m10/mu[i].m00);
    	float cY = (float) (mu[i].m01/mu[i].m00);
    	mc[i] = cv::Point2f( cX, cY);
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(imgContours.at(i)), approx, cv::arcLength(cv::Mat(imgContours.at(i)), true)*0.03, true);

        if(std::fabs(cv::contourArea(imgContours.at(i)) >= 100) &&
        isContourConvex(approx)) {
            if((approx.size() == 3 && typeOfShape == "triangle") ||
            ((approx.size() >= 4 && approx.size() <= 6) &&
                ((typeOfShape == "square" && isSquare(approx) && isRectangularShape(approx)) ||
                (typeOfShape == "rectangle" && !isSquare(approx) && isRectangularShape(approx)))) ||
            ((approx.size() == 5 || approx.size() == 6) && typeOfShape == "semiCircle" && isCircle(approx, circles) && !isRectangularShape(approx)) ||
            (approx.size() > 6 && isCircle(approx, circles) && typeOfShape == "circle")) {
                found = true; 
                timer.stop();
                cv::Scalar color = cv::Scalar(255, 255, 255);
                drawContours(imageContours, imgContours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
                circle(imageContours, mc[i], 4, color, -1, 8, 0);
                if(mode == Mode::INTERACTIVE) {
                    cv::putText(imageContours, "Center point: " + std::to_string(int(cX)) + " " + std::to_string(int(cY)), cv::Point2f(cX - 20, cY -20), CV_FONT_HERSHEY_SIMPLEX, 0.8, color, 2);
                    cv::putText(imageContours, "Area: " + std::to_string((int)(cv::contourArea(approx))), cv::Point2f(cX - 20, cY + 20), CV_FONT_HERSHEY_SIMPLEX, 0.8, color, 2);
                    cv::putText(imageContours, "Time to find: " + std::to_string(timer.getDuration()), cv::Point2f(cX - 20, cY + 40), CV_FONT_HERSHEY_SIMPLEX, 0.8, color, 2);
                } else {
                    std::cout << typeOfShape << " Center point: " << std::to_string(int(cX)) << " " << std::to_string(int(cY)) << std::endl;
                    std::cout << typeOfShape << " Area: " << std::to_string((int) (cv::contourArea(approx))) << std::endl;
                    std::cout << typeOfShape << " Time to find: " << std::to_string(timer.getDuration()) << std::endl;
                }
            }
        }
    }

    if(!found) {
        timer.stop();
        if(mode == Mode::BATCH) {
            std::cout << typeOfShape << " not found" << std::endl;
            std::cout << typeOfShape << " Time to find: " << std::to_string(timer.getDuration()) << std::endl;
        } else {
            cv::putText(imageContours, typeOfShape + " not found", cv::Point2f((float) (imageContours.size().width/2), (float) (imageContours.size().height/2)), CV_FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
            std::cout << typeOfShape << " Time to find: " << std::to_string(timer.getDuration()) << std::endl;
        }
    }

    return imageContours;
}
