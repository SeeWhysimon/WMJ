#include "Project.hpp"

// define yellow
cv::Scalar lower_yellow = cv::Scalar(26, 43, 46);
cv::Scalar upper_yellow = cv::Scalar(34, 255, 255);

// define blue
cv::Scalar lower_blue = cv::Scalar(100, 50, 50);
cv::Scalar upper_blue = cv::Scalar(124, 255, 255);

// define green
cv::Scalar lower_green = cv::Scalar(35, 50, 50);
cv::Scalar upper_green = cv::Scalar(77, 255, 255);

// define red
cv::Scalar lower_red_1 = cv::Scalar(0, 50, 50);
cv::Scalar upper_red_1 = cv::Scalar(10, 255, 255);
cv::Scalar lower_red_2 = cv::Scalar(156, 50, 50);
cv::Scalar upper_red_2 = cv::Scalar(180, 255, 255);

// defin black
cv::Scalar lower_black = cv::Scalar(0, 0, 0);
cv::Scalar upper_black = cv::Scalar(180, 255, 46);

void Image::contour_Shape_Judge(std::vector<std::vector<cv::Point>> contours)
{
	std::vector<std::vector<cv::Point>>conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

    for (int i = 0; i < contours.size(); ++i) {
		int area = cv::contourArea(contours[i]);
		double peri = cv::arcLength(contours[i], true);
		
		cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
		boundRect[i] = cv::boundingRect(conPoly[i]);
		
		// Judge the shape type by the number of corners of contour
		int contour_Corner = (int)conPoly[i].size();
		if (contour_Corner == 3)
			Image::contour_Shapes.push_back("Triangle");
		else if (contour_Corner == 4) {
			double aspRatio = (double)boundRect[i].width / (double)boundRect[i].height;
			if (aspRatio > 0.95 && aspRatio < 1.05) 
				Image::contour_Shapes.push_back("Square");
			else 
				Image::contour_Shapes.push_back("Rectangle");
		}
		else if (contour_Corner > 4)
			Image::contour_Shapes.push_back("Circle");
	}
}

void Image::find_black_contour(cv::Mat src)
{	
	std::vector<std::vector<cv::Point>> blackContour;
	cv::Mat blackOnly;
	cv::inRange(src, lower_black, upper_black, blackOnly);
	cv::findContours(blackOnly, blackContour, Image::hierarchy, 
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : blackContour) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Black");
	}

	Image::contour_Shape_Judge(blackContour);
}

void Image::find_yellow_contour(cv::Mat src)
{	
	std::vector<std::vector<cv::Point>> yellowContour;
	cv::Mat yellowOnly;
	cv::inRange(src, lower_yellow, upper_yellow, yellowOnly);
	cv::findContours(yellowOnly, yellowContour, Image::hierarchy, 
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : yellowContour) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Yellow");
	}

	Image::contour_Shape_Judge(yellowContour);
}

void Image::find_blue_contour(cv::Mat src)
{
	std::vector<std::vector<cv::Point>> blueContour;
	cv::Mat blueOnly;
	cv::inRange(src, lower_blue, upper_blue, blueOnly);
	cv::findContours(blueOnly, blueContour, Image::hierarchy, 
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : blueContour) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Blue");
	}

	Image::contour_Shape_Judge(blueContour);
}

void Image::find_green_contour(cv::Mat src)
{
	std::vector<std::vector<cv::Point>> greenContour;
	cv::Mat greenOnly;
	cv::inRange(src, lower_green, upper_green, greenOnly);
	cv::findContours(greenOnly, greenContour, Image::hierarchy, 
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : greenContour) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Green");
	}

	Image::contour_Shape_Judge(greenContour);
}

void Image::find_red_contour(cv::Mat src)
{
	std::vector<std::vector<cv::Point>> redContour1, redContour2;
	cv::Mat redOnly1, redOnly2;
	
	// Red mask 1
	cv::inRange(src, lower_red_1, upper_red_1, redOnly1);
	cv::findContours(redOnly1, redContour1, Image::hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : redContour1) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Red");
	}

	//Red mask 2
	cv::inRange(src, lower_red_2, upper_red_2, redOnly2);
	cv::findContours(redOnly2, redContour2, Image::hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto& i : redContour2) {
		Image::contours.push_back(i);
		Image::contour_Colors.push_back("Red");
	}

	Image::contour_Shape_Judge(redContour1);
	Image::contour_Shape_Judge(redContour2);
}



void Image::contour_Init(cv::Mat src)
{
	cv::Mat srcHSV;
	cv::cvtColor(src, srcHSV, cv::COLOR_BGR2HSV);
	
	Image::find_black_contour(srcHSV);
	Image::find_blue_contour(srcHSV);
	Image::find_green_contour(srcHSV);
	Image::find_red_contour(srcHSV);
	Image::find_yellow_contour(srcHSV);
}

void Image::show_Info(cv::Mat dst)
{	
	cv::drawContours(dst, Image::contours, -1, cv::Scalar(126, 126, 126), 5);
	for (int i = 0; i < Image::contours.size(); ++i) {
		cv::putText(dst, std::to_string(i), 
			{Image::contours[i][0].x, Image::contours[i][0].y}, 
			cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0, 69, 255), 5);
		std::cout << i << "\t" << Image::contour_Shapes[i] << "\t" << Image::contour_Colors[i] << std::endl;
	}
}
