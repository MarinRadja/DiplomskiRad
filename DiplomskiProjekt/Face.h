#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>

using namespace cv;
using namespace cv::dnn;
using namespace std;
using namespace dlib;

class Face {
private:
public:
	matrix<rgb_pixel> face;
	matrix<float, 0, 1> face_descriptor;
	std::string image_location;

	Face();
	Face(matrix<rgb_pixel> _face);
};

