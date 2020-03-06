#ifndef COLORDETECTOR_HPP
#define COLORDETECTOR_HPP

#include "Timer.hpp"
#include "Configure.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

class ColorDetector {
    public:
        ColorDetector();
        virtual ~ColorDetector();

        static cv::Mat detectColor(cv::Mat& image,const ColorConfiguration& colorConfiguration, Timer& timer);
};

#endif
