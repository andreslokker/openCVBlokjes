#include "Configure.hpp"
#include <iostream>
#include <fstream>

std::string Configure::colors[NR_OF_COLORS] = { "red", "green", "blue",
		"yellow", "black", "white" };
ColorConfiguration Configure::colorConfiguration[NR_OF_COLORS] = { };
cv::Mat Configure::picture;
int Configure::currentSlider = 0;
cv::Mat Configure::inRangePicture;

Configure::Configure(ObjectDetector* objectDetector) :
		objectDetector(objectDetector), configFile("./config") {

}

Configure::~Configure() {

}

void Configure::onTrackbar(int, void*) {
	cv::cvtColor(inRangePicture, inRangePicture, CV_BGR2GRAY);
	cv::cvtColor(picture, picture, CV_BGR2HSV);
	cv::inRange(picture,
			cv::Scalar(colorConfiguration[currentSlider].hsvHMin,
					colorConfiguration[currentSlider].hsvSMin,
					colorConfiguration[currentSlider].hsvVMin),
			cv::Scalar(colorConfiguration[currentSlider].hsvHMax,
					colorConfiguration[currentSlider].hsvSMax,
					colorConfiguration[currentSlider].hsvVMax), inRangePicture);
	cv::cvtColor(picture, picture, CV_HSV2BGR);
	cv::cvtColor(inRangePicture, inRangePicture, CV_GRAY2BGR);
	cv::bitwise_and(picture, inRangePicture, inRangePicture);
}

void Configure::startConfiguration() {
	std::ofstream myConfigFile;
	myConfigFile.open(configFile, std::ios::trunc);
	for (int i = 0; i < NR_OF_COLORS; i++) {
		colorConfiguration[i].color = colors[i];
		std::string windowName = "configuring window "
				+ colorConfiguration[i].color;
		cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
		cv::createTrackbar("HSV H Min " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvHMin, 180,
				Configure::onTrackbar);
		cv::createTrackbar("HSV H Max " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvHMax, 180,
				Configure::onTrackbar);
		cv::createTrackbar("HSV S Min " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvSMin, 255,
				Configure::onTrackbar);
		cv::createTrackbar("HSV S Max " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvSMax, 255,
				Configure::onTrackbar);
		cv::createTrackbar("HSV V Min " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvVMin, 255,
				Configure::onTrackbar);
		cv::createTrackbar("HSV V Max " + colorConfiguration[i].color,
				windowName, &colorConfiguration[i].hsvVMax, 255,
				Configure::onTrackbar);

		std::cout << "press space to finish color: "
				<< colorConfiguration[i].color << std::endl;

		while (true) {
			picture = objectDetector->getWebcamImage();
			picture.copyTo(inRangePicture);
			void* b;
			onTrackbar(int(), b);

			cv::namedWindow("configuring window");
			cv::imshow("configuring window", inRangePicture);
			cv::imshow("Camera window", picture);

			char c = (char) cv::waitKey(30);
			if (c == ' ') {
				cv::destroyWindow(windowName);

				myConfigFile
						<< colorConfiguration[i].color << " "
								<< colorConfiguration[i].hsvHMin << " "
								<< colorConfiguration[i].hsvHMax << " "
								<< colorConfiguration[i].hsvSMin << " "
								<< colorConfiguration[i].hsvSMax << " "
								<< colorConfiguration[i].hsvVMin << " "
								<< colorConfiguration[i].hsvVMax << " \n";
				break;
			}
		}
		currentSlider++;
	}
	myConfigFile.close();
}

void Configure::parseLine(std::string input, unsigned short lineCount)
{
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	unsigned short count = 0;
	while ((pos = input.find(delimiter)) != std::string::npos) {
	    token = input.substr(0, pos);
	    input.erase(0, pos + delimiter.length());
	    switch (count){
	    case 0: colorConfiguration[lineCount].color = token;
	    break;
	    case 1: colorConfiguration[lineCount].hsvHMin = std::stoi(token);
	    break;
	    case 2: colorConfiguration[lineCount].hsvHMax = std::stoi(token);
	    break;
	    case 3: colorConfiguration[lineCount].hsvSMin = std::stoi(token);
	    break;
	    case 4: colorConfiguration[lineCount].hsvSMax = std::stoi(token);
	    break;
	    case 5: colorConfiguration[lineCount].hsvVMin = std::stoi(token);
	    break;
	    case 6: colorConfiguration[lineCount].hsvVMax = std::stoi(token);
	    break;

	    }
	    count++;
	}
}

void Configure::readConfiguration()
{
	std::ifstream myfile(configFile);
	std::string input;

	if (myfile.is_open()) {
		unsigned short lineCount = 0;
		while (std::getline(myfile, input)) {
	           parseLine(input, lineCount);
	           lineCount++;
		}
	}
}

ColorConfiguration Configure::getColorConfiguration(std::string color) {
	for(unsigned short i = 0; i < NR_OF_COLORS; i++)
	{
		if(colorConfiguration[i].color == color) return colorConfiguration[i];
	}
	std::cout << "Color unknown, using red color" << std::endl;
	return colorConfiguration[0];
}
