#pragma once

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>


#include "Face.h"
#include "FaceGraph.h"

#include "json.hpp"

class FaceCluster {
private:
	std::vector<Face> faces;
public:
	void addFace(Face face);
	void removeFace(int i);

	int getNFaces();

	Face* getFacePtr(size_t i_face);

	std::vector<Face>* getFaces();
	std::vector<Face>::iterator getIterator();    
	
	std::vector<Face>::iterator begin() { return faces.begin(); }
	std::vector<Face>::const_iterator begin() const { return faces.begin(); }
	std::vector<Face>::iterator end() { return faces.end(); }
	std::vector<Face>::const_iterator end() const { return faces.end(); }
};

class FaceGraph {
private:
	unsigned long numberOfClusters;

	std::vector<sample_pair> edges;
	std::vector<unsigned long> labels;

	std::vector<Face> faces;
	std::vector<FaceCluster> face_clusters;
public:
	void addFace(Face face);
	void addFace(matrix<rgb_pixel>& _face, string& _image_location, string& _img_name);
	Face* getFacePtr(int i);
	std::vector<Face>* getFacesPtr();
		
	void addEdge(size_t i, size_t j);
	std::vector<sample_pair>* getEdges();

	std::vector<unsigned long>* getLabelsPtr();

	void setNumberOfClusters(unsigned long n);
	unsigned long getNumberOfClusters();
	void sortFacesIntoClusters();
	
	FaceCluster* getClusterPtr(size_t i_cluster);

	void saveGraphToJson(string& json_name);
};