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

void RunAlgorithm::runAlgorithm(std::string path, std::string device, std::string framework) {
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
            face_detector.detectFaceOpenCVDNN(resized, framework, imageName, imageLocation);
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
// add next button