#include "Configure.hpp"
#include "ColorDetector.hpp"
#include "ShapeDetector.hpp"
#include "FileReader.hpp"
#include <iostream>

int main(int argc, char **argv)
{
//    cv::Mat image = cv::imread(cv::String("pictures/picture2.jpg"));
//    Configure configure;
//    //configure.startConfiguration();
//    std::pair<std::string, std::string> goal("square", "red");
//    ColorDetector colorDetector;
//    cv::Mat thresholdImage = colorDetector.detectColor(image, goal.second);
//    ShapeDetector shapeDetector;
//    cv::Mat finalImage = shapeDetector.detectShape(thresholdImage, goal.first);
//
//    while(true) {
//        cv::imshow("start image", image);
//        cv::imshow("image", finalImage);
//
//        char key = (char) cv::waitKey(30);
//        if (key == 'q' || key == 27) {
//            break;
//        }
//    }

	bool batchMode = false;
	if (argc == 2)
	{
		FileReader fileReader(argv[1]);
		fileReader.readFile();
		std::queue<std::pair<std::string, std::string>> inputQueue =
				fileReader.getInputQueue();
		batchMode = true;
		while (!inputQueue.empty())
		{
			std::cout << inputQueue.front().first << std::endl;
			inputQueue.pop();
		}
	}else
	{
		Parser parser;
	}
	return 0;
}
