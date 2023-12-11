#include "Utils.h"

float Utils::faceSimilarityThreshold = 0.5f;

wxImage Utils::simple_wx_from_mat(std::string imageLocation) {
    cv::Mat img = imread(imageLocation, cv::IMREAD_COLOR);
    cv::Mat im2;
    if (img.channels() == 1) {
        cvtColor(img, im2, cv::COLOR_GRAY2RGB);
    } else if (img.channels() == 4) {
        cvtColor(img, im2, cv::COLOR_BGRA2RGB);
    } else {
        cvtColor(img, im2, cv::COLOR_BGR2RGB);
    }
    long imsize = im2.rows * im2.cols * im2.channels();
    wxImage wx(im2.cols, im2.rows, (unsigned char*)malloc(imsize), false);
    unsigned char* s = im2.data;
    unsigned char* d = wx.GetData();
    for (long i = 0; i < imsize; i++) { 
        d[i] = s[i]; 
    }
    return wx;
}

wxImage Utils::simple_wx_from_mat(cv::Mat& img) {
    long imsize = img.rows * img.cols * img.channels();
    wxImage wx(img.cols, img.rows, (unsigned char*)malloc(imsize), false);
    unsigned char* s = img.data;
    unsigned char* d = wx.GetData();
    for (long i = 0; i < imsize; i++) { 
        d[i] = s[i]; 
    }
    return wx;
}

cv::Mat* Utils::simple_mat_from_wx(wxImage& wx) {
    cv::Mat im2(cv::Size(wx.GetWidth(), wx.GetHeight()), CV_8UC3, wx.GetData());
    cv::cvtColor(im2, im2, cv::COLOR_RGB2BGR);
    return &im2;
}