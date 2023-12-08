#include "FaceGraph.h"

void FaceCluster::addFace(Face face) {
	faces.push_back(face);
}

void FaceCluster::removeFace(int i) {
	if (i >= faces.size()) return;
	faces.erase(faces.begin() + i);
}

void FaceGraph::addFace(Face face) {
	faces.push_back(face);
}

void FaceGraph::addFace(matrix<rgb_pixel> _face, string _image_location) {
	Face face(_face, _image_location);
	faces.push_back(face);
}

Face* FaceGraph::getFacePtr(int i) {
	return &faces.at(i);
}

std::vector<Face>* FaceGraph::getFacesPtr() {
	return &faces;
}

void FaceGraph::addEdge(size_t i, size_t j) {
	edges.push_back(simple_pair(i, j));
}

std::vector<sample_pair>* FaceGraph::getEdges() {
	return &edges;
}

std::vector<unsigned long>* FaceGraph::getLabelsPtr() {
	return &labels;
}

void FaceGraph::setNumberOfClusters(unsigned long n) {
	numberOfClusters = n;
}

unsigned long FaceGraph::getNumberOfClusters() {
	return numberOfClusters;
}
