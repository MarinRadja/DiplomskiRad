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

#include "Face.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;
using namespace dlib;

class FaceDetector
{
public:
	std::vector<matrix<rgb_pixel>> faces;
	std::vector<Face> newFaces;

	FaceDetector();
	void detectFaceOpenCVDNN(Net net, Mat& cvImg, string framework, string imgName);
private:
	size_t inWidth;
	size_t inHeight;
	double inScaleFactor;
	float confidenceThreshold;
	Scalar meanVal;
};

