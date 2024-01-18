#pragma once
#define _WINSOCKAPI_
#include "Face.h"
#include "FaceGraph.h"
#include "IDs.h"
#include "Utils.h"

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

#include <wx/app.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>

using namespace cv;
using namespace std;
using namespace dlib;

class FaceDetector
{
public:	
	template <long num_filters, typename SUBNET> using con5d = con<num_filters, 5, 5, 2, 2, SUBNET>;
	template <long num_filters, typename SUBNET> using con5 = con<num_filters, 5, 5, 1, 1, SUBNET>;

	template <typename SUBNET> using downsampler = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16, SUBNET>>>>>>>>>;
	template <typename SUBNET> using rcon5 = relu<affine<con5<45, SUBNET>>>;

	using net_type = loss_mmod<con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

	std::string face_detector_location = "./models/dlib/mmod_human_face_detector.dat";
	std::string shape_predictor_location = "./models/dlib/shape_predictor_5_face_landmarks.dat";
	std::vector<matrix<rgb_pixel>> faces;
	std::vector<Face> newFaces;
	FaceGraph* face_graph;

	FaceDetector();
	FaceDetector(FaceGraph *_face_graph);
	void detectFaceOpenCVDNN(Mat& cvImg, string framework, string imgName, string imageLocation);
private:
	size_t inWidth;
	size_t inHeight;
	double inScaleFactor;
	float confidenceThreshold;
	Scalar meanVal;
	frontal_face_detector detector;
	net_type face_detector_net;
	shape_predictor sp;

	int ncuda;
};

