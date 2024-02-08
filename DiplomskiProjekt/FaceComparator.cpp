#include "FaceComparator.h"

FaceComparator::FaceComparator(FaceGraph* _face_graph, FaceDetector* faceDetector) {
    face_graph = _face_graph;
    fd = faceDetector;
    deserialize(resnetModelLocation) >> net;
}

void FaceComparator::clusterFaces() {
    cout << "total of " << fd->faces.size() << " faces" << endl;

    // get face embeddings
    face_descriptors = net(fd->faces);

    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::NN_DONE));
    // iterate over all embeddings
    
    //// for each face, get it's embedding
    //for (int i = 0; i < face_descriptors.size(); i++) {
    //    Face face = fd->newFaces.at(i);
    //    face.setFaceDescriptor(face_descriptors.at(i));

    //    groupUpFace(face);
    //}

    //for (int i = 0; i < face_descriptors.size(); i++) {
    //    // face_graph->getFacePtr(i)->setFaceDescriptor(face_descriptors.at(i));
    //    // fd->newFaces.at(i).setFaceDescriptor(face_descriptors.at(i));
    //}

    for (size_t i = 0; i < face_descriptors.size(); ++i) {
        for (size_t j = i; j < face_descriptors.size(); ++j) {
            // add option for user input treshold
            float dist = dlib::length(face_descriptors.at(i)
                - face_descriptors.at(j));
            if (dist < Utils::faceSimilarityThreshold)
                face_graph->addEdge(i, j);
            wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::COMPARED_FACE));
        }
    }
    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_COMPARING_FACES));

    face_graph->setNumberOfClusters(chinese_whispers(*face_graph->getEdges(), *face_graph->getLabelsPtr()));
    face_graph->sortFacesIntoClusters();
    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_CLUSTERING_FACES));


    /*while (face_descriptors.size() > 0) {
        if (!faceEmbeddingExists(face_descriptors.size() - 1)) {
            std::vector<matrix<float, 0, 1>> newFaceGroup;
            newFaceGroup.push_back(face_descriptors.at(face_descriptors.size() - 1));
            face_groups.push_back(newFaceGroup);
        }
        face_descriptors.pop_back();
    }*/

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
