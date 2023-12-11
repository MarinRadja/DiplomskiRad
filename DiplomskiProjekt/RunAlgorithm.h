#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include <wx/wx.h>

#include "FaceDetector.h"
#include "FaceComparator.h"
#include "FaceGraph.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;
namespace fs = std::filesystem;

class RunAlgorithm {
private:
	string caffeConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/deploy.prototxt";
	string caffeWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";

	string tensorflowConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector.pbtxt";
	string tensorflowWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector_uint8.pb";

	std::vector<fs::path> allImages;

	void getAll(fs::path dir, string ext);
	Mat resizeImage(Mat& image, int width = 0, int height = 0, int inter = INTER_AREA);

	FaceDetector face_detector;
	FaceComparator face_comparator;
	FaceGraph face_graph;

public:
	RunAlgorithm();
	void runAlgorithm(std::string path, std::string device = "cpu", std::string framework = "caffe");
	FaceGraph* getFaceGraph();
};

