#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP
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
        Configure();
        virtual ~Configure();
        void startConfiguration();
        static void onTrackbar(int, void*);
    private:
        static std::string colors[NR_OF_COLORS];
        static ColorConfiguration colorConfiguration[NR_OF_COLORS];
        static cv::Mat picture;
        static cv::Mat inRangePicture;
        static int currentSlider;
};

#endif