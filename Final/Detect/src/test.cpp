#include "Project.hpp"

int main(int argv, char** argc) {
    cv::VideoCapture cap(argc[1]);
    if (!cap.isOpened()) {
        std::cout << "Fail to open the file" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame, frame_hsv_ori;
        Armor armor;
        cap >> frame;
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        std::vector<cv::Rect> rects;

        // Check the status of frame
        if (frame.empty()) {
            std::cout << "Blank frame" << std::endl;
            break;
        }

        armor.armorInit(frame, contours, hierarchy, rects);
        armor.showInfo(frame);
        cv::imshow("Video", frame);

        char c = cv::waitKey(25);
        if (c == ' ')
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}