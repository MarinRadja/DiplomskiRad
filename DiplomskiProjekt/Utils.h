#pragma once
#define _WINSOCKAPI_

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include <dlib/matrix.h>
#include <dlib/pixel.h>
#include <dlib/opencv.h>

#include <wx/event.h>
#include <wx/image.h>
#include <wx/bitmap.h>

namespace fs = std::filesystem;

class Utils {
private:
public:
    static float faceSimilarityThreshold;
    static wxImage simple_wx_from_mat(std::string imageLocation);
    static wxImage simple_wx_from_mat(cv::Mat& img);
    static cv::Mat* simple_mat_from_wx(wxImage& wx);
    static int sumUpToIncluding(int n);
    static void convertMatRGBPixelToCVMat(dlib::matrix<dlib::rgb_pixel>& face, cv::Mat& cvImage);
    static void createDirectory(std::string dirName);
};

wxDECLARE_EVENT(myEVT_CREATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(myEVT_UPDATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_SHOW_CLUSTERED_FACES_WINDOW, wxCommandEvent);