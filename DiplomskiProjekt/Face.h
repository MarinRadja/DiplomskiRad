#pragma once
#define _WINSOCKAPI_
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include "json.hpp"

#include "Utils.h"

using namespace cv;
using namespace std;
using namespace dlib;

class Face {
private:
	string image_location;
	string face_location;

	static std::atomic<unsigned int> face_counter;

	std::string saveFaceToDisk(matrix<rgb_pixel>& face, string& _img_name);
public:

	Face();
	Face(matrix<rgb_pixel>& _face, string& _image_location, string& _img_name);
	Face(string _image_location, string _face_location);

	string getImageLocation();
	string getFaceLocation();

	nlohmann::json getJson();

	void setImageLocation(string _image_location);
};

