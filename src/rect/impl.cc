#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray,thre;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::cvtColor(input,gray,cv::COLOR_BGR2GRAY);
    cv::threshold(gray, thre, 50, 255, cv::THRESH_BINARY);
    cv::findContours(thre,contours,hierachy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    cv::Rect boundary_Rect;
    cv::RotatedRect minRect;
    for(size_t i=0;i<contours.size();i++){
        boundary_Rect=cv::boundingRect(contours[i]);
        minRect=cv::minAreaRect(contours[i]);
        double area=cv::contourArea(contours[i]);
        double rectArea=boundary_Rect.area();
        double rArea=minRect.size.area();
        if(fabs(rArea-rectArea)<(0.2)*rectArea && fabs(area-rectArea)<(0.2)*rectArea){
            res=std::make_pair(boundary_Rect,minRect);
            break;
        }
    }
    return res;
}