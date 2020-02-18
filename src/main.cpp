#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

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
    Mat imgMultiply;
    Mat imgEdges;
    
    cvtColor(img, imgHsv, COLOR_BGR2HSV);
    inRange(imgHsv, Scalar(0, 30, 0), Scalar(10, 255, 255), imgTreshold);
    cvtColor(imgTreshold, imgTreshold, COLOR_GRAY2BGR);
    cvtColor(imgTreshold, imgTreshold, COLOR_BGR2HSV);
    multiply(imgTreshold, imgHsv, imgMultiply);
    Canny(imgMultiply, imgEdges, 100, 200);
    cvtColor(imgEdges, imgEdges, COLOR_GRAY2BGR);
    cvtColor(imgEdges, imgEdges, COLOR_BGR2HSV);

    while(true) {
        imshow("normal picture", img);
        imshow("img detected", imgTreshold);
        imshow("multiply", imgMultiply);
        imshow("edged pictures", imgEdges);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    return 0;
}