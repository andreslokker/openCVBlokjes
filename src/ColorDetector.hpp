#ifndef COLORDETECTOR_HPP
#define COLORDETECTOR_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

class ColorDetector {
    public:
        ColorDetector();
        virtual ~ColorDetector();

        cv::Mat detectColor(cv::Mat& image, const std::string& color);
};

#endif