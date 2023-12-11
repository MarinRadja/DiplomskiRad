#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>

#include <wx/event.h>
#include <wx/image.h>
#include <wx/file.h>
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

wxDECLARE_EVENT(EVT_SHOW_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_SHOW_CLUSTERED_FACES_WINDOW, wxCommandEvent);
