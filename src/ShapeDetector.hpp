#ifndef SHAPEDETECTOR_HPP
#define SHAPEDETECTOR_HPP

#include "Timer.hpp"
#include "InputHandler.hpp"
#include "ArgumentParser.hpp"
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

class ShapeDetector {
    public:
        ShapeDetector();
        virtual ~ShapeDetector();

        bool isCircle(std::vector<cv::Point>& approx, std::vector<cv::Vec3f>& circles);
        bool isRectangularShape(std::vector<cv::Point>& approx);
        bool isSquare(std::vector<cv::Point>& approx);

        /* 
        @brief this function will try to detect a given type of shape
        */
        cv::Mat detectShape(cv::Mat& image, const std::string& typeOfShape, Timer& timer, Mode mode);
};

#endif