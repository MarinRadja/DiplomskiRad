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

using namespace cv;
using namespace cv::dnn;
using namespace std;
namespace fs = std::filesystem;

class RunAlgorithm {
private:
	inline static string caffeConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/deploy.prototxt";
	inline static string caffeWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";

	inline static string tensorflowConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector.pbtxt";
	inline static string tensorflowWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector_uint8.pb";

	static std::vector<fs::path> allImages;

	static void getAll(fs::path dir, string ext);
	static Mat resizeImage(Mat& image, int width = 0, int height = 0, int inter = INTER_AREA);
public:
	static void runAlgorithm(std::string path, std::string device = "cpu", std::string framework = "caffe");
};

