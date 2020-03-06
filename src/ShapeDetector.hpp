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
        /**
         * @brief Construct a new Shape Detector object
         * 
         */
        ShapeDetector();

        /**
         * @brief Destroy the Shape Detector object
         * 
         */
        virtual ~ShapeDetector();

        /**
         * @brief This function checks if a given approx is in the circles vector
         * 
         * @param approx Approxes calculated with ApproxPolyDP on a contour
         * @param circles Circles found using the HoughCircles method
         * @return true In case the approx is in the found circles
         * @return false In case the approx is not in the found circles
         */
        static bool isCircle(std::vector<cv::Point>& approx, std::vector<cv::Vec3f>& circles);

        /**
         * @brief This function checks if a given approx has the shape of a rectangle
         * 
         * @param approx Approxes calculated with ApproxPolyDP on a contour
         * @return true In case the approx has the shape of a rectangular shape
         * @return false In case the approx does not has the shape of a rectangular shape
         */
        static bool isRectangularShape(std::vector<cv::Point>& approx);

        /**
         * @brief This function checks if a given approx has the shape of a square (checks for 4 sides with the same length)
         * 
         * @param approx Approxes calculated with ApproxPolyDP on a contour
         * @return true In case the approx has the shape of a square shape
         * @return false In case the approx does not has the shape of a square shape
         */
        static bool isSquare(std::vector<cv::Point>& approx);

        /**
         * @brief This function can be used to detect given type of shapes on a given image.
         * 
         * @param image The image where this function will look for the shape (image must be in greyscale)
         * @param typeOfShape Type of shape to look for (rectangle, square, circle etc.)
         * @param timer Timer object which is needed to determine the time needed to find the shapes. The timer needs to be started before calling this function
         * @param mode Type of application mode, see Enum Mode.
         * @return cv::Mat With the contours of the found shapes.
         */
        static cv::Mat detectShape(cv::Mat& image, const std::string& typeOfShape, Timer& timer, Mode mode);
};

#endif