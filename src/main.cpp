#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int blockSize = 2;
int apertureSize = 3;
double k = 0.04;

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
        for(int y = 0; y < imgCountours.at(i).size(); y++) {
            std::cout << imgCountours.at(i).at(y) << std::endl;
        }
        std::cout << "end" << std::endl;
        double area = contourArea(imgCountours.at(i));
        std::cout << area << std::endl;
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