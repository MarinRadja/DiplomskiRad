#pragma once
#define _WINSOCKAPI_

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include <wx/event.h>
#include <wx/image.h>
#include <wx/bitmap.h>


class Utils
{
private:
public:
	static float faceSimilarityThreshold; 
    static wxImage simple_wx_from_mat(std::string imageLocation);
    static wxImage simple_wx_from_mat(cv::Mat& img);
    static cv::Mat* simple_mat_from_wx(wxImage& wx);
};

wxDECLARE_EVENT(myEVT_CREATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(myEVT_UPDATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_SHOW_CLUSTERED_FACES_WINDOW, wxCommandEvent);
