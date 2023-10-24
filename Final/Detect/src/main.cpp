#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

// Data collected from https://qr.ae/pKrUDM
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

// Editable
double distDetect (double img_height, double real_height, double focal_len, double obj_height, double sensor_height) {
    return focal_len * img_height * real_height / (obj_height * sensor_height);
}

// Editable
std::string sizeDetect(double obj_height, double distance) {
    double tan = obj_height / distance;
    if (tan > 1) 
        return "Big";
    else 
        return "Small";
}

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
    num = "";

    for (int i = 0; i < 10; ++i) {
        cv::Mat temp = cv::imread("../src_pic/" + std::to_string(i) + ".png");
        cv::cvtColor(temp, temp, cv::COLOR_BGR2HSV);
        cv::resize(temp, temp, cv::Size(48, 48), 0, 0, cv::INTER_LINEAR);
        cv::resize(image, image, cv::Size(48, 48), 0, 0, cv::INTER_LINEAR);
        cv::absdiff(temp, image, imgSub);
        rate = getPixelSum(imgSub);
        // Editable  18900 < rate < 18950
        if (rate < min) {
            min = rate;
            
            num = std::to_string(i);
        }
    }
}
//***********************************************************//


int main(int argv, char** argc) {
    cv::VideoCapture cap(argc[1]);
    
    if (!cap.isOpened()) {
        std::cout << "Fail to open the file" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame, frame_hsv_ori;
        cap >> frame;
        std::vector<std::vector<cv::Point>> contours_old, contours_new;
        std::vector<cv::Vec4i> hierarchy;
        std::vector<cv::Rect> rects;
        if (frame.empty()) {
            std::cout << "Blank frame" << std::endl;
            break;
        }
        // Process the frame
        cv::cvtColor(frame, frame_hsv_ori, cv::COLOR_BGR2HSV);
        cv::GaussianBlur(frame_hsv_ori, frame_hsv_ori, cv::Size(5, 5), 0, 0);
        
        // Find the contours of blue armor
        cv::Mat frame_hsv_blue;
        cv::inRange(frame_hsv_ori, lower_blue_hsv, upper_blue_hsv, frame_hsv_blue);
        cv::findContours(frame_hsv_blue, contours_old, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Find contours with size > 50 and draw their bounding rectangles
        for (int i = 0; i < contours_old.size(); ++i) {
            double area = cv::contourArea(contours_old[i]);
            if (area > 50) {
                contours_new.push_back(contours_old[i]);
                rects.push_back(cv::boundingRect(contours_old[i]));
            }
        }

        if (!contours_new.empty()) {
            double distance_d = distDetect(img_height, real_height, focal_len, rects[0].height, sensor_height);
            std::string Size = sizeDetect(rects[0].height, distance_d);
            std::string distance_str = std::to_string(distance_d / 1000);
            cv::putText(frame, "Blue ", cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
            cv::putText(frame, distance_str + "m", cv::Point(20, 200), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
            cv::putText(frame, Size, cv::Point(20, 300), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
        }

        // Draw a rectangle contour
        for (int i = 0; i < rects.size(); ++i) 
            cv::rectangle(frame, rects[i], cv::Scalar(126, 255, 126), 8);
        

        // Clear all the pre-information
        contours_new.clear(); contours_old.clear(); hierarchy.clear(); rects.clear(); 
        
        // Number detection
        cv::Mat frame_hsv_white;
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
        cv::findContours(frame_hsv_white, contours_old, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < contours_old.size(); ++i) {
            cv::Rect rect = cv::boundingRect(contours_old[i]);
            
            // Editable
            if (((rect.height > 50 && rect.height < 5000) && (rect.width > 50 && rect.width < 5000)) && (rect.area() < 20000)) {
                
                double ratio = (double)rect.width / (double) rect.height;
                if (ratio < 1.5 && ratio > 0.5) {
                    contours_new.push_back(contours_old[i]);
                    rects.push_back(cv::boundingRect(contours_old[i]));
                }
            }
        }
        for (int i = 0; i < rects.size(); ++i) 
            cv::rectangle(frame, rects[i], cv::Scalar(128, 255, 255), 5);
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
            cv::putText(frame, matchingNum, cv::Point(600, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(128, 255, 255), 5);
        }

        cv::imshow("Video", frame);

        char c = cv::waitKey(25);
        if (c == ' ')
            break;
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}