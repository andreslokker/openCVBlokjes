#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int blockSize = 2;
int apertureSize = 3;
double k = 0.04;


std::pair<uint16_t, uint16_t> findCenterPointImg(const std::vector<Point>& points) {
    uint16_t minXValue = points.at(0).x;
    uint16_t maxXValue = points.at(0).x;
    uint16_t minYValue = points.at(0).y;
    uint16_t maxYValue = points.at(0).y;

    for(int i = 0; i < points.size(); i++) {
        if(points.at(i).x < minXValue) {
            minXValue = points.at(i).x;
        } else if(points.at(i).x > maxXValue) {
            maxXValue = points.at(i).x;
        }

        if(points.at(i).y < minYValue) {
            minYValue = points.at(i).y;
        } else if(points.at(i).y > maxYValue) {
            maxYValue = points.at(i).y;
        }
    }
    return std::pair<uint16_t, uint16_t>(minXValue + maxXValue - minXValue, minYValue + maxYValue - minYValue);
}

int main(int argc, char** argv) {
    namedWindow("normal picture");
    namedWindow("img detected");
    namedWindow("multiply");
    namedWindow("edged pictures");
    String imageName("pictures/picture.png");
    Mat img = imread(imageName);
    Mat imgHsv;
    Mat imgTreshold;
    Mat imgTresholdHsv;
    Mat imgMultiply;
    Mat imgEdges;
    
    blur(img, img, Size(5,5));
    cvtColor(img, imgHsv, COLOR_BGR2HSV);
    inRange(imgHsv, Scalar(0, 30, 0), Scalar(10, 255, 255), imgTreshold);
    erode(imgTreshold, imgTreshold, getStructuringElement(MORPH_RECT, Size(9,9), Point(-1,-1)));
    dilate(imgTreshold, imgTreshold, getStructuringElement(MORPH_RECT, Size(9,9), Point(-1,-1)));
    
    //cvtColor(imgTreshold, imgTreshold, COLOR_GRAY2BGR);
    //cvtColor(imgTreshold, imgTreshold, COLOR_BGR2HSV);
    //multiply(imgTreshold, imgHsv, imgMultiply);
    Canny(imgTreshold, imgEdges, 50, 100);
    

    std::vector<std::vector<Point>> imgCountours;
    std::vector<Vec4i> hierarchy;
    findContours(imgTreshold, imgCountours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    
    Mat drawing = Mat::zeros( imgTreshold.size(), CV_8UC3 );
    RNG rng(12345);
    for( size_t i = 0; i< imgCountours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, imgCountours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    for(int i = 0; i < imgCountours.size(); i++) {
        if(imgCountours.at(i).size() >= 1) {
            std::pair<uint16_t, uint16_t> centerPoint = findCenterPointImg(imgCountours.at(i));
            std::cout << "Point:" << std::endl;
            std::cout << centerPoint.first << std::endl;
            std::cout << centerPoint.second << std::endl;
        }
        //double area = contourArea(imgCountours.at(i));
        //std::cout << area << std::endl;
    }
    
    cvtColor(imgEdges, imgEdges, COLOR_GRAY2BGR);
    cvtColor(imgEdges, imgEdges, COLOR_BGR2HSV);


    while(true) {
        imshow("normal picture", img);
        imshow("img detected", imgTreshold);
        //imshow("multiply", imgMultiply);
        imshow("edged pictures", imgEdges);
        imshow( "Contours", drawing );

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    return 0;
}