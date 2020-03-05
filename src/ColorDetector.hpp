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
        /**
         * @brief Construct a new Color Detector object
         * 
         */
        ColorDetector();
        
        /**
         * @brief Destroy the Color Detector object
         * 
         */
        virtual ~ColorDetector();
        
        /**
         * @brief Filter out the color which is given from the colorconfiguration and present it in a new image
         * 
         * @param image input image
         * @param colorConfiguration the configuration values from the color which is to be found 
         * @param timer  a timer to count how long it takes to find the specific color
         * @return cv::Mat the output image in which the searched color is represented in
         */
        cv::Mat detectColor(cv::Mat& image,const ColorConfiguration& colorConfiguration, Timer& timer);
};

#endif
