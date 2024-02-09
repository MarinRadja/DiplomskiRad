#include "FaceComparator.h"

FaceComparator::FaceComparator(FaceGraph* _face_graph, FaceDetector* faceDetector) {
    face_graph = _face_graph;
    fd = faceDetector;
    deserialize(resnetModelLocation) >> net;
}

void FaceComparator::clusterFaces() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    // get face embeddings
    auto start1 = high_resolution_clock::now();
    face_descriptors = net(fd->faces);
    face_graph->nnFacesTime = since(start1).count();

    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::NN_DONE));

    auto start2 = high_resolution_clock::now();

    int count = 0;
    for (size_t i = 0; i < face_descriptors.size(); ++i) {
        for (size_t j = i; j < face_descriptors.size(); ++j) {
            // add option for user input treshold
            float dist = dlib::length(face_descriptors.at(i)
                - face_descriptors.at(j));
            if (dist < Utils::faceSimilarityThreshold)
                face_graph->addEdge(i, j);

            count++;
            if (count % 1000 == 0) {
                wxCommandEvent* comparedFaceEvent = new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::COMPARED_FACE);
                comparedFaceEvent->SetInt(count);
                wxTheApp->QueueEvent(comparedFaceEvent);
            }
        }
    }
    face_graph->comparingFacesTime = since(start2).count();

    wxCommandEvent* comparedFaceEvent = new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::COMPARED_FACE);
    comparedFaceEvent->SetInt(count);
    wxTheApp->QueueEvent(comparedFaceEvent);
    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_COMPARING_FACES));

    start2 = std::chrono::high_resolution_clock::now();
    face_graph->setNumberOfClusters(chinese_whispers(*face_graph->getEdges(), *face_graph->getLabelsPtr(), 1000));
    face_graph->cwTime = since(start2).count();

    face_graph->sortFacesIntoClusters();
    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_CLUSTERING_FACES));
}
