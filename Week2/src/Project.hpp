#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class Image {
public:
	void contour_Init(cv::Mat);
	
	void contour_Shape_Judge(std::vector<std::vector<cv::Point>>);
	
	// Find color types 
	void find_yellow_contour(cv::Mat);
	void find_blue_contour(cv::Mat);
	void find_green_contour(cv::Mat);
	void find_red_contour(cv::Mat);
	void find_black_contour(cv::Mat);

	void show_Info(cv::Mat);

private:
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::string> contour_Shapes;
	std::vector<std::string> contour_Colors;
};
