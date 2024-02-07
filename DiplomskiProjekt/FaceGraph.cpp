#include "FaceGraph.h"

FaceCluster::FaceCluster() {}

FaceCluster::FaceCluster(int _cluster_id, std::string _cluster_name) {
	cluster_id = _cluster_id;
	cluster_name = _cluster_name;
}

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

nlohmann::json FaceCluster::getJson() {
	nlohmann::json faces_json;
	for (Face fa : faces) {
		faces_json.push_back(fa.getJson());
	}

	nlohmann::json clusterJson = {
		{"cluster_id", cluster_id},
		{"cluster_name", cluster_name},
		{"faces", faces_json}
	};
	return clusterJson;
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
		graph_json.push_back(faCl.getJson());
	}

	Utils::saveToDisk(graph_json, json_name);
}

void FaceGraph::loadGraphFromJson(string& json_name) {
	nlohmann::json graphJson;
	Utils::loadFromDisk(graphJson, json_name);

	for (auto& [clusterIndex, clusterJson] : graphJson.items()) {
		FaceCluster faceCluster(clusterJson.at("cluster_id"),
			clusterJson.at("cluster_name"));
		for (auto& [faceIndex, faceJson] : clusterJson.at("faces").items()) {
			Face face(faceJson.at("image_location"), 
				faceJson.at("face_location"),
				faceJson.at("face_name"));
			faceCluster.addFace(face);
		}
		face_clusters.push_back(faceCluster);
	}
	numberOfClusters = face_clusters.size();
}
