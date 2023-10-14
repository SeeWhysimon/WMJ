#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>

#define EVENT_MOUSEMOVE 0
#define EVENT_LBUTTONDOWN 1
#define EVENT_RBUTTONDOWN 2 
#define EVENT_MBUTTONDOWN 3   
#define EVENT_LBUTTONUP 4
#define EVENT_RBUTTONUP 5
#define EVENT_MBUTTONUP 6
#define EVENT_LBUTTONDBLCLK 7
#define EVENT_RBUTTONDBLCLK 8
#define EVENT_MBUTTONDBLCLK 9

cv::Mat background;

// Position of the object
double obj_y = 0;
double obj_x = 0;

// Position of the target(mouse)
double target_y = 0;
double target_x = 0;

double force_y = 0;
double force_x = 0;

double total_force_y = 0;
double total_force_x = 0;

double acceleration_y = 0;
double acceleration_x = 0;

double velocity_y = 0;
double velocity_x = 0;

// Error between target_position and obj_position
double err_y = 0;
double err_x = 0;

// Last error between target_position and obj_position
double last_err_y = 0;
double last_err_x = 0;

// Integratino error at the position (x, y)
double integration_sum_y = 0;
double integration_sum_x = 0;

// Derivative error of at the position (x, y)
double derivative_y = 0;
double derivative_x = 0;

// Threshold of integration error
double integration_thr_y = 1000;
double integration_thr_x = 1000;

double m = 1;
// Fraction coefficient
double u = 0.5;
double dt = 0.05;

int kp = 0, ki = 0  , kd = 0;
double Kp, Ki, Kd;

double pidResolve_y(double t_err, double kp, double ki, double kd) {
    err_y = t_err;
    integration_sum_y += err_y / 100;
    
    if (abs(integration_sum_y) > integration_thr_y) 
        integration_sum_y = integration_thr_y * abs(integration_sum_y) / integration_sum_y;
    
    derivative_y = err_y - last_err_y;
    last_err_y = err_y;
    
    double delta = kp * err_y + ki * integration_sum_y + kd * derivative_y;
    return delta;
}

double pidResolve_x(double t_err, double kp, double ki, double kd)
{
    err_x = t_err;
    integration_sum_x += err_x / 100;
    
    if (abs(integration_sum_x) > integration_thr_x) 
        integration_sum_x = integration_thr_x * abs(integration_sum_x) / integration_sum_x;
    
    derivative_x = err_x - last_err_x;
    last_err_x = err_x;
    
    double delta = kp * err_x + ki * integration_sum_x + kd * derivative_x;
    return delta;
}


void mouseEvent(int event, int x, int y, int flags, void *ustc)
{
	if (event == EVENT_MOUSEMOVE) {
		target_y = y;
        target_x = x;
	}
}

void on_trackbar_p(int ,void*) {
    Kp = kp / 100.0;
}

void on_trackbar_i(int ,void*) {
    Ki = ki / 100.0;
    integration_sum_y = 0;
    integration_sum_x = 0;
}

void on_trackbar_d(int ,void*) {
    Kd = kd / 10.0;
}

// Draw a cross at mouse's position
void drawCross(cv::Mat src) {
	cv::line(src, cv::Point(target_x + 10, target_y), cv::Point(target_x - 10, target_y), cv::Scalar(255, 255, 255), 2);
	cv::line(src, cv::Point(target_x, target_y + 10), cv::Point(target_x, target_y - 10), cv::Scalar(255, 255, 255), 2);
}

int main()
{
    cv::namedWindow("img");
    cv::setMouseCallback("img", mouseEvent);
    cv::createTrackbar("Kp", "img", &kp, 100, on_trackbar_p);
    cv::createTrackbar("Ki", "img", &ki, 100, on_trackbar_i);
    cv::createTrackbar("Kd", "img", &kd, 500, on_trackbar_d);
    on_trackbar_p(0, NULL);
    on_trackbar_i(0, NULL);
    on_trackbar_d(0, NULL);

    while(true) {
        background = cv::Mat::zeros(1200, 1200, CV_8UC3);
        drawCross(background);
    
        std::string P = std::to_string(Kp);
        std::string I = std::to_string(Ki);
        std::string D = std::to_string(Kd);
        std::string X_mouse = std::to_string(target_x);
        std::string Y_mouse = std::to_string(target_y);
        std::string X_obj = std::to_string(obj_x);
        std::string Y_obj = std::to_string(obj_y);
        
        // Print the current information
        cv::putText(background, "Kp = " + P, cv::Point(20, 50), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);
        cv::putText(background, "Ki = " + I, cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);
        cv::putText(background, "Kd = " + D, cv::Point(20, 150), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);
        cv::putText(background, "Mouse = ( " + X_mouse + " , " + Y_mouse + " )", cv::Point(320, 50), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);
        cv::putText(background, "Object = ( " + X_obj + " , " + Y_obj + " )", cv::Point(320, 100), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);

        force_y = pidResolve_y(target_y - obj_y, Kp, Ki, Kd);
        force_x = pidResolve_x(target_x - obj_x, Kp, Ki, Kd);

        total_force_y = force_y - m * 10 - u * velocity_y;
        total_force_x = force_x - m * 10 - u * velocity_x;

        acceleration_y = total_force_y / m;
        acceleration_x = total_force_x / m;

        velocity_y += acceleration_y * dt;
        velocity_x += acceleration_x * dt;

        obj_y += velocity_y * dt;
        obj_x += velocity_x * dt;

        // Reset object if it touches the boundary of background
        if (obj_y <= 0 || obj_y >= 1200) {
            obj_y = 0;
            total_force_y = 0;
            acceleration_y = 0;
            velocity_y = 0;
        }
        if (obj_x <= 0 || obj_x >= 1200) {
            obj_x = 0;
            total_force_x = 0;
            acceleration_x = 0;
            velocity_x = 0;
        }

        cv::circle(background, cv::Point(obj_x, obj_y), 10, cv::Scalar(200, 200, 200), -1);

        if ((fabs(obj_x - target_x) <= 1e-5) && (fabs(obj_y - target_y) <= 1e-6)) 
            cv::putText(background, "Matched!", cv::Point(320, 150), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);
        else
            cv::putText(background, "Unmatched...", cv::Point(320, 150), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 1, 8, false);

        cv::imshow("img", background);
        
        char c = cv::waitKey(10);
        if (c == ' ') 
            break;
    }
    return 0;
}