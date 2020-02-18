#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int hue_max = 179;
int hRangeMax = 20;

int hValue = 0;
int hRange = 0;
int sValue = 0;
int vValue = 0;

Mat img, imgHsv, imgTreshold;

void change_hsv(int, void*)
	{
//		cvtColor(img, imgHsv, COLOR_BGR2HSV);
		if(hValue - hRange <= 0) hValue = 0;
		if(hValue + hRange >= 179) hValue = 179;
	    inRange(imgHsv, Scalar(hValue - hRange, 30, 0), Scalar(hValue + hRange, 255, 255), imgTreshold);
//		cvtColor(imgHsv, COLOR_)
//	    inRange(imgHsv, Scalar(0, 30, 0), Scalar(10, 255, 255), imgTreshold);
	}

int main(int argc, char** argv) {
    namedWindow("normal picture");
    namedWindow("img detected");
    String imageName("./Test1.jpg");
    Mat img = imread(imageName);
    pyrDown(img, img, Size(img.cols/2, img.rows/2));

    cvtColor(img, imgHsv, COLOR_BGR2HSV);
    inRange(imgHsv, Scalar(0, 30, 0), Scalar(10, 255, 255), imgTreshold);

    namedWindow("Trackbars", CV_WINDOW_AUTOSIZE);
    createTrackbar("Hue", "Trackbars", &hValue, hue_max, change_hsv);
    createTrackbar("Hue range", "Trackbars", &hRange, hRangeMax, change_hsv);

    while(true) {
        imshow("normal picture", img);
        imshow("img detected", imgTreshold);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    return 0;
}
