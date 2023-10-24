#include "Project.hpp"

// Device parameters
double focal_len = 50;
double sensor_height = 36;
double real_height = 70; // optional?
double img_height = 640;

// Define the boundary of white
cv::Scalar lower_white_hsv = cv::Scalar(0, 0, 100);
cv::Scalar upper_white_hsv = cv::Scalar(255, 64, 255);
// Define the boundary of red
cv::Scalar lower_red_hsv = cv::Scalar(0, 70, 127);
cv::Scalar upper_red_hsv = cv::Scalar(20, 255, 255);
// Define the boundary of blue
cv::Scalar lower_blue_hsv = cv::Scalar(110, 100, 120);
cv::Scalar upper_blue_hsv = cv::Scalar(180, 255, 255);

//***********************************************************//
// Pixel comparing
int getPixelSum(cv::Mat& image) {
    int a = 0;
    for (int row = 0; row < image.rows; ++row) {
        uchar* current_pixel = image.ptr<uchar>(row);
        for (int col = 0; col < image.cols; ++col) {
            a += *current_pixel++;
        }
    }
    return a;
}
void imgMatch(cv::Mat& image, int& rate, std::string& num) {
    cv::Mat imgSub;
    double min = 10e5;
    for (int i = 0; i < 10; ++i) {
        cv::Mat temp = cv::imread("../src_pic/" + std::to_string(i) + ".png");
        cv::cvtColor(temp, temp, cv::COLOR_BGR2HSV);
        cv::resize(temp, temp, cv::Size(48, 48), 0, 0, cv::INTER_LINEAR);
        cv::resize(image, image, cv::Size(48, 48), 0, 0, cv::INTER_LINEAR);
        cv::absdiff(temp, image, imgSub);
        rate = getPixelSum(imgSub);
        if (rate < min) {
            min = rate;
            num = std::to_string(i);
        }
    }
}
//***********************************************************//

// Detect the distance between the camera and the armor
void Armor::distDetect (double img_height, double real_height, double focal_len, double obj_height, double sensor_height) {
    Armor::Distance = focal_len * img_height * real_height / (obj_height * sensor_height);
}

// Judging the size of the armor (size judging criteria editable)
void Armor::sizeDetect(double obj_height, double distance) {
    double tan = obj_height / distance;
    if (tan > 1) 
        Armor::Size = "Big";
    else 
        Armor::Size = "Small";
}

// Judge the color of the armor
void Armor::colorDetect(cv::Mat frame, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy) {
    cv::Mat frame_hsv_ori;
    std::vector<std::vector<cv::Point>> contours_temp;
    
    cv::cvtColor(frame, frame_hsv_ori, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(frame_hsv_ori, frame_hsv_ori, cv::Size(5, 5), 0, 0);
    cv::Mat frame_hsv_blue;
    cv::inRange(frame_hsv_ori, lower_blue_hsv, upper_blue_hsv, frame_hsv_blue);
    cv::findContours(frame_hsv_blue, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Find the contours of blue armor with size > 50
    for (int i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > 50) 
            contours_temp.push_back(contours[i]);
    }
    if (!contours_temp.empty()) {
        Armor::Color = "Blue";
        cv::Rect rect = cv::boundingRect(contours_temp[0]);
        Armor::obj_height = rect.height;
    }
    // If the blue armor was not found, try to find red armor
    else {
        // Clean up the fromer trash
        contours.clear(); contours_temp.clear(); hierarchy.clear(); 

        cv::Mat frame_hsv_red;
        cv::inRange(frame_hsv_ori, lower_red_hsv, upper_red_hsv, frame_hsv_red);
        cv::findContours(frame_hsv_red, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        // Find the contours of red armor with size > 50
        for (int i = 0; i < contours.size(); ++i) {
            double area = cv::contourArea(contours[i]);
            if (area > 50) 
                contours_temp.push_back(contours[i]);
        }
        if (!contours_temp.empty()) {
            Armor::Color = "Red";
            cv::Rect rect = cv::boundingRect(contours_temp[0]);
            Armor::obj_height = rect.height;
        }
        else {
            // Clean up the fromer trash
            contours.clear(); contours_temp.clear(); hierarchy.clear();
            Armor::Color = "Gray";
        }
    }
}

void Armor::numberDetect(cv::Mat frame, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy, std::vector<cv::Rect> rects) {
    contours.clear(); hierarchy.clear(); rects.clear();
    // Number detection
    cv::Mat frame_hsv_white, frame_hsv_ori;
    cv::cvtColor(frame, frame_hsv_ori, cv::COLOR_BGR2HSV);
        
    // Process the frame
    cv::inRange(frame_hsv_ori, lower_white_hsv, upper_white_hsv, frame_hsv_white);
    cv::GaussianBlur(frame_hsv_white, frame_hsv_white, cv::Size(5, 5), 0, 0);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::erode(frame_hsv_white, frame_hsv_white, element);
    cv::GaussianBlur(frame_hsv_white, frame_hsv_white, cv::Size(5, 5), 0, 0);
    cv::dilate(frame_hsv_white, frame_hsv_white, element);
    cv::erode(frame_hsv_white, frame_hsv_white, element);
    cv::dilate(frame_hsv_white, frame_hsv_white, element);
    cv::dilate(frame_hsv_white, frame_hsv_white, element);

    // Rebuild the `contours_new` and `rects` from `frame_hsv_white`
    cv::findContours(frame_hsv_white, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); ++i) {
        cv::Rect rect = cv::boundingRect(contours[i]);

        if (((rect.height > 50 && rect.height < 5000) && (rect.width > 50 && rect.width < 5000)) && (rect.area() < 20000)) { // Editable
            double ratio = (double)rect.width / (double) rect.height;
            if (ratio < 1.5 && ratio > 0.5) 
                rects.push_back(rect);
        }
    }
    //*************************************************************//
    cv::Mat final[rects.size()];
    std::string matchingNum = "";
    int matchingRate = 0;
    for (int i = 0; i < rects.size(); ++i) {
        frame(rects[i]).copyTo(final[i]);
        imgMatch(final[i], matchingRate, matchingNum);
    }
    //***********************************************************//
    if (matchingRate < 10e6) {
        Armor::Number = matchingNum;
    }
    contours.clear(); hierarchy.clear(); rects.clear();
}

void Armor::armorInit(cv::Mat frame, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy, std::vector<cv::Rect> rects) {
    Armor::colorDetect(frame, contours, hierarchy);
    if (Armor::Color != "Gray") {
        Armor::distDetect(img_height, real_height, focal_len, Armor::obj_height, sensor_height);
        Armor::sizeDetect(Armor::obj_height, Armor::Distance);
        Armor::numberDetect(frame, contours, hierarchy, rects);
    }
}

void Armor::showInfo(cv::Mat frame) {
    std::string distance_str = std::to_string(Armor::Distance / 1000);

    if (Armor::Color == "Blue") 
        cv::putText(frame, Armor::Color, cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255, 50, 50), 5);
    else if (Armor::Color == "Red")
        cv::putText(frame, Armor::Color, cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(50, 50, 255), 5);
    else 
        cv::putText(frame, Armor::Color, cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 128, 128), 5);
    cv::putText(frame, distance_str + " m", cv::Point(20, 200), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
    cv::putText(frame, Armor::Size, cv::Point(20, 300), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
    cv::putText(frame, Armor::Number, cv::Point(20, 400), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
}