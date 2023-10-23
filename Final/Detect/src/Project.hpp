#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Armor {
public:
    void distDetect (double, double, double, double, double);
    void sizeDetect(double, double);
    void colorDetect(cv::Mat, std::vector<std::vector<cv::Point>>, std::vector<cv::Vec4i>);
    void numberDetect(cv::Mat, std::vector<std::vector<cv::Point>>, std::vector<cv::Vec4i>, std::vector<cv::Rect>);
    void armorInit(cv::Mat, std::vector<std::vector<cv::Point>>, std::vector<cv::Vec4i>, std::vector<cv::Rect>);
    void showInfo(cv::Mat);
private:
    double obj_height = 100000000.0;
    double Distance = 0.0;
    std::string Size = "";
    std::string Color = "";
    std::string Number = "";
};