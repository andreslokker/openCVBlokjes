#include "Configure.hpp"
#include <iostream>

std::string Configure::colors[NR_OF_COLORS] = {"red", "green", "blue", "yellow", "black", "white"};
ColorConfiguration Configure::colorConfiguration[NR_OF_COLORS] = {};
cv::Mat Configure::picture;
int Configure::currentSlider = 0;
cv::Mat Configure::inRangePicture;

Configure::Configure() {

}

Configure::~Configure() {

}

void Configure::onTrackbar(int, void*) {
    cv::cvtColor(inRangePicture, inRangePicture, CV_BGR2GRAY);
    cv::cvtColor(picture, picture, CV_BGR2HSV);
    cv::inRange(picture, 
    cv::Scalar(colorConfiguration[currentSlider].hsvHMin, colorConfiguration[currentSlider].hsvSMin, colorConfiguration[currentSlider].hsvVMin),
    cv::Scalar(colorConfiguration[currentSlider].hsvHMax, colorConfiguration[currentSlider].hsvSMax, colorConfiguration[currentSlider].hsvVMax),
    inRangePicture);
    cv::cvtColor(picture, picture, CV_HSV2BGR);
    cv::cvtColor(inRangePicture, inRangePicture, CV_GRAY2BGR);
    cv::bitwise_and(picture, inRangePicture, inRangePicture);
}

void Configure::startConfiguration() {
    cv::VideoCapture cap;
    int deviceID = 2;
    cap.open(deviceID);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    for(int i = 0; i < NR_OF_COLORS; i++) {
        colorConfiguration[i].color = colors[i];
        std::string windowName = "configuring window " + colorConfiguration[i].color;
        cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
        cv::createTrackbar("HSV H Min " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvHMin, 180, Configure::onTrackbar);
        cv::createTrackbar("HSV H Max " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvHMax, 180, Configure::onTrackbar);
        cv::createTrackbar("HSV S Min " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvSMin, 255, Configure::onTrackbar);
        cv::createTrackbar("HSV S Max " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvSMax, 255, Configure::onTrackbar);
        cv::createTrackbar("HSV V Min " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvVMin, 255, Configure::onTrackbar);
        cv::createTrackbar("HSV V Max " + colorConfiguration[i].color, windowName, &colorConfiguration[i].hsvVMax, 255, Configure::onTrackbar);

        std::cout << "press space to finish color: " << colorConfiguration[i].color << std::endl;

        while(true) {
            cap.read(picture);
            picture.copyTo(inRangePicture);
            void* b;
            onTrackbar(int(), b);

            cv::namedWindow("configuring window");
            cv::imshow("configuring window", inRangePicture);

            char c = (char) cv::waitKey(30);
            if(c == ' ') {
                cv::destroyWindow(windowName);
                break;
            }
        }

        currentSlider++;
    }
    cap.release();
}