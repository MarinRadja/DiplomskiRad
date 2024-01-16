#include "FaceGraph.h"

void FaceCluster::addFace(Face face) {
	faces.push_back(face);
}

void FaceCluster::removeFace(int i) {
	if (i >= faces.size()) return;
	faces.erase(faces.begin() + i);
}

int FaceCluster::getNFaces() {
	return faces.size();
}

Face* FaceCluster::getFacePtr(size_t i_face) {
	return &faces.at(i_face);
}

void FaceGraph::addFace(Face face) {
	faces.push_back(face);
}

void FaceGraph::addFace(matrix<rgb_pixel>& _face, string& _image_location, string& _img_name) {
	Face face(_face, _image_location, _img_name);
	faces.push_back(face);
}

Face* FaceGraph::getFacePtr(int i) {
	return &faces.at(i);
}

std::vector<Face>* FaceGraph::getFacesPtr() {
	return &faces;
}

void FaceGraph::addEdge(size_t i, size_t j) {
	edges.push_back(sample_pair(i, j));
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

void FaceGraph::sortFacesIntoClusters() {
	face_clusters.resize(numberOfClusters);

	for (size_t cluster_id = 0; cluster_id < numberOfClusters; ++cluster_id) {
		std::vector<Face> temp;
		for (size_t j = 0; j < labels.size(); ++j) {
			if (cluster_id == labels[j])
				face_clusters[cluster_id].addFace(faces[j]);
		}
	}
}

FaceCluster* FaceGraph::getClusterPtr(size_t i_cluster) {
	return &face_clusters.at(i_cluster);
}

int FaceGraph::getNFacesFromClusterAt(size_t i_cluster) {
	return face_clusters.at(i_cluster).getNFaces();
}

void FaceGraph::saveGraphToJson(string& json_name) {
	nlohmann::json graph_json;
	for (FaceCluster faCl : face_clusters) {
		nlohmann::json cluster_json;
		for (Face fa : faCl) {
			cluster_json.push_back(fa.getJson());
		}
		graph_json.push_back(cluster_json);
	}

	Utils::saveToDisk(graph_json, json_name);
}

void FaceGraph::loadGraphFromJson(string& json_name) {
	nlohmann::json graphJson;
	Utils::loadFromDisk(graphJson, json_name);

	for (auto& [clusterIndex, clusterJson] : graphJson.items()) {
		FaceCluster faceCluster;
		for (auto& [faceIndex, faceJson] : clusterJson.items()) {
			Face face(faceJson.at("image_location"), faceJson.at("face_location"));
			faceCluster.addFace(face);
		}
		face_clusters.push_back(faceCluster);
	}
	numberOfClusters = face_clusters.size();
}
