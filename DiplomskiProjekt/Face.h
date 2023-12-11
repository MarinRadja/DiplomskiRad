#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace cv;
using namespace std;
using namespace dlib;

class Face {
private:
	matrix<rgb_pixel> face;
	matrix<float, 0, 1> face_descriptor;
	string image_location;
public:

	Face();
	Face(matrix<rgb_pixel> _face);
	Face(matrix<rgb_pixel>& _face, string _image_location);

	string getImageLocation();
	matrix<float, 0, 1> getFaceDescriptor();
	matrix<rgb_pixel> getFace();
	matrix<rgb_pixel> *getFacePtr();
	Mat getFaceOpenCV();

	void setImageLocation(string _image_location);
	void setFaceDescriptor(matrix<float, 0, 1> _face_descriptor);
	void setFace(matrix<rgb_pixel> _face);

	float distanceFromFace(Face otherFace);
};

