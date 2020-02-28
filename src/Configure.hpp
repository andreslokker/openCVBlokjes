#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP

#include "ObjectDetector.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

#define NR_OF_COLORS 6

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
        Configure(ObjectDetector* objectDetector);
        virtual ~Configure();
        void startConfiguration();
        static void onTrackbar(int, void*);
        void parseLine(std::string input, unsigned short lineCount);
        void readConfiguration();
	static ColorConfiguration getColorConfiguration(std::string color);

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
