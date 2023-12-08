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

#include "Face.h"
#include "FaceGroup.h"

using namespace cv;
using namespace std;
using namespace dlib;

class FaceDetector
{
public:
	std::vector<matrix<rgb_pixel>> faces;
	std::vector<Face> newFaces;

	FaceDetector();
	void detectFaceOpenCVDNN(Mat& cvImg, string framework, string imgName, string imageLocation);
private:
	size_t inWidth;
	size_t inHeight;
	double inScaleFactor;
	float confidenceThreshold;
	Scalar meanVal;
	frontal_face_detector detector;
	shape_predictor sp;
};

