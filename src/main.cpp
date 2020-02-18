#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char** argv) {
    namedWindow("normal picture");
    namedWindow("img detected");
    String imageName("pictures/picture.png");
    Mat img = imread(imageName);
    Mat imgHsv;
    Mat imgTreshold;
    cvtColor(img, imgHsv, COLOR_BGR2HSV);
    inRange(imgHsv, Scalar(0, 30, 0), Scalar(10, 255, 255), imgTreshold);

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