#pragma once
#define _WINSOCKAPI_
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include <dlib/clustering.h>  
 
#include "FaceDetector.h"
#include "Face.h"
#include "Utils.h"
#include "IDs.h"



using namespace cv;
using namespace std;



template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;
using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<
	alevel0<
	alevel1<
	alevel2<
	alevel3<
	alevel4<
	max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2,
	input_rgb_image_sized<150>
	>>>>>>>>>>>>;


class FaceComparator {
public:
	FaceComparator(FaceGraph* _face_graph, FaceDetector* faceDetector);
	~FaceComparator() {};

	void clusterFaces();

	anet_type net;
	std::vector<matrix<float, 0, 1>> face_descriptors;
private:
	FaceDetector* fd;
	FaceGraph* face_graph;

	// for development use this location
	// std::string resnetModelLocation = "E:/Programming/_Projects/DiplomskiProjekt/x64/Release/models/dlib/dlib_face_recognition_resnet_model_v1.dat";
	
	// for release use this location
	std::string resnetModelLocation = "./models/dlib/dlib_face_recognition_resnet_model_v1.dat";
	std::vector<std::vector<matrix<float, 0, 1>>> face_groups;
	std::vector<std::vector<Face>> new_face_groups;

	void groupFacesIntoClusters();
};

