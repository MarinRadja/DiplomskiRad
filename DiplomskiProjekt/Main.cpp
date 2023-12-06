#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

#include <wx/wx.h>

#include "FaceDetector.h"
#include "FaceComparator.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;
namespace fs = std::filesystem;


const string caffeConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/deploy.prototxt";
const string caffeWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";

const string tensorflowConfigFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector.pbtxt";
const string tensorflowWeightFile = "E:/Programming/_Projects/DiplomskiProjekt/models/opencv_face_detector_uint8.pb";


std::vector<fs::path> getAll(fs::path dir, string ext) {
    std::vector<fs::path> paths;

    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (auto& entry : fs::recursive_directory_iterator(dir)) {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
                fs::path p = entry.path();
                paths.emplace_back(p.make_preferred());
            }
        }
    }

    return paths;
}

Mat resizeImage(Mat& image, int width = 0, int height = 0, int inter = INTER_AREA) {
    int h = image.rows, w = image.cols;

    cout << h << ", " << w << endl;

    if (width == 0 && height == 0)  return image;
    else if (width == 0) {
        float ratio = 1. * height / h;
        h = height;
        w = w * ratio;
    }
    else if (height == 0) {
        float ratio = 1. * width / w;
        h = h * ratio;
        w = width;
    }
    else {
        h = height;
        w = width;
    }

    cout << h << ", " << w << endl;

    Mat resizedImage;
    resize(image, resizedImage, Size(w, h));

    return resizedImage;
}   

void runAlgorithm(std::string path, std::string device = "cpu", std::string framework = "caffe") {

    Net net;

    if (framework == "caffe")
        net = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
    else
        net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);

#if (CV_MAJOR_VERSION >= 4)
    if (device == "CPU")
    {
        net.setPreferableBackend(DNN_TARGET_CPU);
    }
    else
    {
        net.setPreferableBackend(DNN_BACKEND_CUDA);
        net.setPreferableTarget(DNN_TARGET_CUDA);
    }
#else
    // force CPU backend for OpenCV 3.x as CUDA backend is not supported there
    net.setPreferableBackend(DNN_BACKEND_DEFAULT);
    device = "cpu";
#endif





    FaceDetector fd;


    //fd.detectFaceOpenCVDNN(net, s1, framework, "ja");
    //fd.detectFaceOpenCVDNN(net, s2, framework, "ja_i_sestre");

    string imageSetDirectory = path;
    std::vector<string> extension;
    extension.push_back(".jpg");
    extension.push_back(".jpeg");

    for (const auto& ext : extension) {
        for (const auto& entry : getAll(imageSetDirectory, ext)) {
            cout << "Proccesing image: " << entry.string() << endl;
            Mat cvImg1 = imread(entry.string(), IMREAD_COLOR);
            Mat resized = resizeImage(cvImg1, 800);

            fd.detectFaceOpenCVDNN(net, resized, framework, entry.stem().string());
        }
    }

    FaceComparator fc(&fd);
    fc.clusterFaces();
}
