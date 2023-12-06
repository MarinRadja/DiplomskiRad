#include "FaceComparator.h"

FaceComparator::FaceComparator(FaceDetector* faceDetector) {
	this->fd = faceDetector;
}

void FaceComparator::clusterFaces() {
    anet_type net;
    deserialize(resnetModelLocation) >> net;

    cout << "total of " << fd->faces.size() << " faces" << endl;

    // get face embeddings
    face_descriptors = net(fd->faces);
    // iterate over all embeddings

    while (face_descriptors.size() > 0) {
        if (!faceEmbeddingExists(face_descriptors.size() - 1)) {
            std::vector<matrix<float, 0, 1>> newFaceGroup;
            newFaceGroup.push_back(face_descriptors.at(face_descriptors.size() - 1));
            face_groups.push_back(newFaceGroup);
        }
        face_descriptors.pop_back();
    }
}

bool FaceComparator::faceEmbeddingExists(int x) {
    float minDist = std::numeric_limits<float>::max();
    int pos = -1;
    for (int i = 0; i < face_groups.size(); i++) {
        float dist = 0.f;
        for (matrix<float, 0, 1> face : face_groups.at(i)) {
            dist += abs(length(face) - length(face_descriptors.at(x)));
        }
        dist /= face_groups.at(i).size();
        
        if (dist < minDist) {
            minDist = dist;
            pos = i;
        }
    }

    if (minDist < Utils::faceSimilarityThreshold) {
        face_groups.at(pos).push_back(face_descriptors.at(x));
        return true;
    }
    return false;
}