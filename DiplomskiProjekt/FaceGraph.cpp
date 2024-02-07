#include "FaceGraph.h"

FaceCluster::FaceCluster() : FaceCluster(0, "") {}

FaceCluster::FaceCluster(int _cluster_id, std::string _cluster_name) : FaceCluster(_cluster_id, _cluster_name, false) {
}

FaceCluster::FaceCluster(int _cluster_id, std::string _cluster_name, bool _selected) {
	cluster_id = _cluster_id;
	cluster_name = _cluster_name;
	selected = _selected;
}

void FaceCluster::addFace(Face face) {
	faces.push_back(face);
}

bool FaceCluster::removeFace(int i) {
	faces.erase(faces.begin() + i);
	return faces.size() > 0 ? false : true;
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
		{"selected", selected},
		{"faces", faces_json}
	};
	return clusterJson;
}

bool FaceCluster::removeIfSelectedMatches(bool isSelected) {
	for (size_t j = 0; j < faces.size(); j++) {
		if (faces[j].selected == isSelected) {
			removeFace(j);
			j--;
		}
	}
	return faces.size() > 0 ? false : true;
}

void FaceCluster::selectAllFaces(bool _select) {
	for (Face& f : faces)
		f.selected = _select;	
}

bool FaceCluster::allSelected() {
	for (int i = 0; i < faces.size(); i++) {
		if (faces[i].selected == false) {
			return false;
		}
	}
	return true;
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
	return face_clusters.size();
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
			clusterJson.at("cluster_name"), 
			clusterJson.at("selected"));
		for (auto& [faceIndex, faceJson] : clusterJson.at("faces").items()) {
			bool sel = faceJson.at("selected");
			Face face(faceJson.at("image_location"), 
				faceJson.at("face_location"),
				faceJson.at("face_name"),
				faceJson.at("face_id"),
				sel);
			faceCluster.addFace(face);
		}
		face_clusters.push_back(faceCluster);
	}
	numberOfClusters = face_clusters.size();
}

void FaceGraph::removeIfSelectedMatches(bool isSelected) {
	std::vector<FaceCluster>::iterator it = face_clusters.begin();
	while (it != face_clusters.end()) {
		if (it->removeIfSelectedMatches(isSelected)) {
			it = face_clusters.erase(it);
		} else ++it;
	}
}

bool FaceGraph::removeFace(int iF, int iC) {
	if (face_clusters[iC].removeFace(iF))
		return removeCluster(iC);

	return false;
}

bool FaceGraph::removeCluster(int iC) {
	face_clusters.erase(face_clusters.begin() + iC);
	return true;
}

void FaceGraph::addCluster(FaceCluster newCluster) {
	face_clusters.push_back(newCluster);
}
