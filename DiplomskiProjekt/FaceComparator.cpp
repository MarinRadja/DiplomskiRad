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
    
    //// for each face, get it's embedding
    //for (int i = 0; i < face_descriptors.size(); i++) {
    //    Face face = fd->newFaces.at(i);
    //    face.setFaceDescriptor(face_descriptors.at(i));

    //    groupUpFace(face);
    //}

    for (int i = 0; i < face_descriptors.size(); i++) {
        fd->newFaces.at(i).setFaceDescriptor(face_descriptors.at(i));
    }

    while (face_descriptors.size() > 0) {
        if (!faceEmbeddingExists(face_descriptors.size() - 1)) {
            std::vector<matrix<float, 0, 1>> newFaceGroup;
            newFaceGroup.push_back(face_descriptors.at(face_descriptors.size() - 1));
            face_groups.push_back(newFaceGroup);
        }
        face_descriptors.pop_back();
    }

    //for (std::vector<Face> groupFaces : new_face_groups) {
    //    for (Face face : groupFaces) {
    //        Mat im;
    //        namedWindow("im");
    //        im = imread(face.getImageLocation());
    //        if (im.empty()) {
    //            break;
    //        }
    //        Mat im2;
    //        resize(im, im2, Size(400, 400));
    //        imshow("im", im2);
    //        waitKey(0);
    //    }
    //}
}

bool FaceComparator::faceEmbeddingExists(int x) {
    float minDist = std::numeric_limits<float>::max();
    int pos = -1;
    for (int i = 0; i < face_groups.size(); i++) {
        float dist = 0.f;
        for (matrix<float, 0, 1> face : face_groups.at(i)) {
            dist += length(face - face_descriptors.at(x));
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

void FaceComparator::groupUpFace(Face face) {
    float minDist = std::numeric_limits<float>::max();
    int pos = -1;

    for (int i = 0; i < new_face_groups.size(); i++) {
        float dist = 0.f;
        for (Face groupedFace : new_face_groups.at(i)) {
            dist += length(groupedFace.getFaceDescriptor() - face.getFaceDescriptor());
        }
        dist /= new_face_groups.at(i).size();

        if (dist < minDist) {
            minDist = dist;
            pos = i;
        }
    }

    if (minDist < Utils::faceSimilarityThreshold) {
        new_face_groups.at(pos).push_back(face);
        return;
    }

    std::vector<Face> newGroupFace;
    newGroupFace.push_back(face);
    new_face_groups.push_back(newGroupFace);
}
