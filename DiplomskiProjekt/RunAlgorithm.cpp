#include "RunAlgorithm.h"

void RunAlgorithm::getAll(fs::path dir, string ext) {
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (auto& entry : fs::recursive_directory_iterator(dir)) {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
                fs::path p = entry.path();
                allImages.emplace_back(p.make_preferred());

                 wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DETECTED_IMAGE));
            }
        }
    }
}

Mat RunAlgorithm::resizeImage(Mat& image, int width, int height, int inter) {
    int h = image.rows, w = image.cols;

    cout << h << ", " << w << endl;

    if (width == 0 && height == 0)  return image;
    else if (width == 0) {
        float ratio = 1. * height / h;
        h = height;
        w = w * ratio;
    } else if (height == 0) {
        float ratio = 1. * width / w;
        h = h * ratio;
        w = width;
    } else {
        h = height;
        w = width;
    }

    cout << h << ", " << w << endl;

    Mat resizedImage;
    resize(image, resizedImage, Size(w, h));

    return resizedImage;
}

RunAlgorithm::RunAlgorithm() : face_graph(), face_detector(&face_graph), face_comparator(&face_graph, &face_detector) {

}

void RunAlgorithm::runAlgorithm(std::string path) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    string imageSetDirectory = path;
    std::vector<string> extension;
    extension.push_back(".jpg");
    extension.push_back(".jpeg");

    for (string ext : extension) {
        getAll(imageSetDirectory, ext);
    }       
    wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_DETECTING_IMAGES));

    for (fs::path entry : allImages) {
            cout << "Proccesing image: " << entry.string() << endl;
            Mat cvImg1 = imread(entry.string(), IMREAD_COLOR);
            Mat resized = resizeImage(cvImg1, 800);

            string imageName = entry.stem().string();
            string imageLocation = entry.string();
            face_detector.detectFaces(resized, imageName, imageLocation);
            wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_DETECTING_FACES_ON_IMAGE));
    }

    wxCommandEvent* doneDetectingFaces = new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DONE_DETECTING_FACES);
    doneDetectingFaces->SetInt(face_detector.faces.size());
    wxTheApp->QueueEvent(doneDetectingFaces);

    face_comparator.clusterFaces();
}

FaceGraph* RunAlgorithm::getFaceGraph() {
    return &face_graph;
}

void RunAlgorithm::searchPeople(std::string img_path) {
    FaceGraph searchTargets;
    FaceDetector newDetector = FaceDetector(&searchTargets);
    FaceComparator newComparator = FaceComparator(&searchTargets, &newDetector);
    std::vector<matrix<float, 0, 1>> face_descriptors;

    filesystem::path _img_path(img_path);

    Mat cvImg1 = imread(img_path, IMREAD_COLOR);
    Mat resized = resizeImage(cvImg1, 800);

    string imageName = _img_path.stem().string();
    string imageLocation = img_path;
    newDetector.detectFaces(resized, imageName, imageLocation);


    face_descriptors = newComparator.net(newDetector.faces);
    
    removeNotFound(face_descriptors, searchTargets.faces);
}

void RunAlgorithm::removeNotFound(std::vector<matrix<float, 0, 1>>& searchTargetsDescriptors, std::vector<Face> &searchTargetsFaces) {
    std::vector<int> foundClusters(searchTargetsDescriptors.size());
    std::vector<Face*> faces;
    if (face_comparator.face_descriptors.size() == 0) {
        std::vector<matrix<rgb_pixel>> facesMat;
        for (int i = 0; i < face_graph.getNumberOfClusters(); i++) {
            for (int j = 0; j < face_graph.getClusterPtr(i)->getNFaces(); j++) {
                facesMat.push_back(load_face(i, j));
                faces.push_back(face_graph.getClusterPtr(i)->getFacePtr(j));
            }
        }
        face_comparator.face_descriptors = face_comparator.net(facesMat);
    }
    std::vector<matrix<float, 0, 1>> facesDescriptors = face_comparator.face_descriptors;

    std::map<int, int> keepClusters;
    FaceGraph reduced;
    int count = 0;
    for (size_t i = 0; i < searchTargetsDescriptors.size(); i++) {
        int nClu = searchClusters(searchTargetsDescriptors[i], facesDescriptors);
        foundClusters[i] = nClu;
        if (nClu != -1) {
            if (keepClusters.find(i) != keepClusters.end()) {
                keepClusters.insert(make_pair(nClu, count++));
                reduced.addCluster(face_graph.face_clusters[i]);
            }
            std::map<int, int>::iterator it = keepClusters.find(nClu);
            reduced.face_clusters[it->second].addFace(searchTargetsFaces[i]);
        }
    }
    ;
}

int RunAlgorithm::searchClusters(matrix<float, 0, 1>& targetDescriptor, std::vector<matrix<float, 0, 1>> &facesDescriptors) {
    for (int i = 0; i < facesDescriptors.size(); i++) {
        float dist = dlib::length(targetDescriptor
            - facesDescriptors.at(i));
        if (dist < Utils::faceSimilarityThreshold)
            return i;
    }
    return -1;
}

matrix<rgb_pixel> RunAlgorithm::load_face(int i, int j) {
    std::string img_path = face_graph.getClusterPtr(i)->getFacePtr(j)->getFaceLocation();
    Mat cvImg1 = imread(img_path, IMREAD_COLOR);
    Mat resized = resizeImage(cvImg1, 800);

    cv_image<bgr_pixel> image(resized);
    matrix<rgb_pixel> dlibImg;
    assign_image(dlibImg, image);

    return dlibImg;
}
