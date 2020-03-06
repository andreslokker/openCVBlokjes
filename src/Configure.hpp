#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

#define NR_OF_COLORS 6

class ObjectDetector;

typedef struct {
    std::string color;
    int hsvHMin;
    int hsvHMax;
    int hsvSMin;
    int hsvSMax;
    int hsvVMin;
    int hsvVMax;
} ColorConfiguration;

class Configure {
    public:
         /**
         * @brief Construct a new Configure object
         * 
         * @param objectDetector 
         */
        explicit Configure(ObjectDetector* objectDetector);
        
        /**
         * @brief Destroy the Configure object
         * 
         */
        virtual ~Configure();
        
        /**
         * @brief startConfiguration, starts up the configuration to update the configuration file
         * 
         */
        void startConfiguration();

         /**
         * @brief onTrackbar Trackbar function, updates the values for the colorConfiguration
         * 
         * @param int
         * @param void*
         */
        static void onTrackbar(int, void*);

        /**
         * @brief Line parser, parses the line and puts them into the colorConfiguration
         * Seperates each section of the input by using a " " as delimeter
         * @param input Input line which is parsed
         * @param lineCount The line number which is read, puts the input into this position of the colorConfiguration
         */
        static void parseLine(std::string input, unsigned short lineCount);

        /**
         * @brief Read the configuration file line by line and calls parseLine function for each line
         * 
         */
        void readConfiguration();

        /**
         * @brief Get the Color Configuration object
         * 
         * @param color string which defines which color should be returned 
         * @return ColorConfiguration 
         */
	static ColorConfiguration getColorConfiguration(std::string& color);

    private:
        static std::string colors[NR_OF_COLORS];
        static ColorConfiguration colorConfiguration[NR_OF_COLORS];
        static cv::Mat picture;
        static cv::Mat inRangePicture;
        static int currentSlider;
        ObjectDetector* objectDetector;
        std::string configFile;
};

#endif
