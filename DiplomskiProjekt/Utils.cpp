#include "Utils.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(myEVT_CREATE_PROGRESS_WINDOW, wxCommandEvent);
wxDEFINE_EVENT(myEVT_UPDATE_PROGRESS_WINDOW, wxCommandEvent);
wxDEFINE_EVENT(EVT_SHOW_CLUSTERED_FACES_WINDOW, wxCommandEvent);

#pragma region "Data"
float Utils::faceSimilarityThreshold = 0.55f;
#pragma endregion "Data"

#pragma region "Functions"

int Utils::sumUpToIncluding(int n) {
    return n * (n + 1) / 2;
}

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

void Utils::convertMatRGBPixelToCVMat(dlib::matrix<dlib::rgb_pixel>& face, cv::Mat& cvImage) {
    cv::Mat original = dlib::toMat(face);

    cv::cvtColor(original, cvImage, cv::COLOR_RGB2BGR);
}

void Utils::createDirectory(std::string dirName) {
    if (!fs::is_directory(dirName) || !fs::exists(dirName)) { // Check if src folder exists
        fs::create_directory(dirName); // create src folder
    }
}

#pragma endregion "Functions"