#pragma once
#define _WINSOCKAPI_

#include "FaceDetector.h"
#include "FaceComparator.h"
#include "FaceGraph.h"
#include "ProgressWindow.h"
#include "Utils.h"
#include "IDs.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include <wx/wx.h>

using namespace cv;
using namespace cv::dnn;
using namespace std;
namespace fs = std::filesystem;

class RunAlgorithm {
private:

	std::vector<fs::path> allImages;

	void getAll(fs::path dir, string ext);
	Mat resizeImage(Mat& image, int width = 0, int height = 0, int inter = INTER_AREA);

	ProgressWindow* progress_window;

	FaceDetector face_detector;
	FaceComparator face_comparator;
	FaceGraph face_graph;
public:
	RunAlgorithm();
	void runAlgorithm(std::string path);
	FaceGraph* getFaceGraph();

	void searchPeople(std::string img_path);
	void removeNotFound(std::vector<matrix<float, 0, 1>> &searchTargets, std::vector<Face>& searchTargetsFaces);
	int searchClusters(matrix<float, 0, 1>& targetDescriptor, std::vector<matrix<float, 0, 1>> &facesDescriptors);
	matrix<rgb_pixel> load_face(int i, int j);
	int getClustID(int nClust);
};

