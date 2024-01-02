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
	// for development use this location
	// std::string shape_predictor_location = "E:/Programming/_Projects/DiplomskiProjekt/x64/Release/models/dlib/shape_predictor_5_face_landmarks.dat";
	
	// for release use this location	
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
	shape_predictor sp;
};

