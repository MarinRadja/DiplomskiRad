#pragma once
#include "FaceGraph.h"

#include "Face.h"

class FaceCluster {
private:
	std::vector<Face> faces;
public:
	void addFace(Face face);
	void removeFace(int i);
};

class FaceGraph {
private:
	unsigned long numberOfClusters;

	std::vector<sample_pair> edges;
	std::vector<unsigned long> labels;

	std::vector<Face> faces;
public:
	void addFace(Face face);
	void addFace(matrix<rgb_pixel> _face, string _image_location);
	Face* getFacePtr(int i);
	std::vector<Face>* getFacesPtr();
		
	void addEdge(size_t i, size_t j);
	std::vector<sample_pair>* getEdges();

	std::vector<unsigned long>* getLabelsPtr();

	void setNumberOfClusters(unsigned long n);
	unsigned long getNumberOfClusters();
};