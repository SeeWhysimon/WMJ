#include "Project.hpp"

int main(int argv, char** argc)
{
    cv::Mat src, dst;
    src = cv::imread(argc[1]);
    dst = src;

    Image image;
    image.contour_Init(src);
    image.show_Info(dst);

    cv::imwrite("../Output.png", dst);
    
    return 0;
}
