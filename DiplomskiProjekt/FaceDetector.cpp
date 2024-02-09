#include "FaceDetector.h"




FaceDetector::FaceDetector()
{
    this->inWidth = 300;
    this->inHeight = 300;
    this->inScaleFactor = 1.0;
    this->confidenceThreshold = 0.7;
    this->meanVal = Scalar(104.0, 177.0, 123.0);

    // get face detector
    detector = get_frontal_face_detector();

    // load face shape detector
    deserialize(shape_predictor_location) >> sp;
}

FaceDetector::FaceDetector(FaceGraph* _face_graph) {
    this->inWidth = 300;
    this->inHeight = 300;
    this->inScaleFactor = 1.0;
    this->confidenceThreshold = 0.7;
    this->meanVal = Scalar(104.0, 177.0, 123.0);

    // get face detector
    detector = get_frontal_face_detector();

    // load face shape detector
    deserialize(shape_predictor_location) >> sp;

    face_graph = _face_graph;
}

int FaceDetector::detectFaces(Mat& cvImg, string imgName, string imageLocation) {
    // convert opencv img format to dlib img format
    Mat cvRGB;
    cvtColor(cvImg, cvRGB, COLOR_BGR2RGB);
    cv_image<rgb_pixel> img1(cvRGB);

    auto foundFaces = detector(img1);

    for (auto face : foundFaces) {
        auto shape = sp(img1, face);

        matrix<rgb_pixel> face_chip;
        extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);

        faces.push_back(move(face_chip));
        face_graph->addFace(faces.back(), imageLocation, imgName);
    }

    return faces.size();
}

void FaceDetector::detectFacesNoEvents(Mat& cvImg, string imgName, string imageLocation) {
    // convert opencv img format to dlib img format
    Mat cvRGB;
    cvtColor(cvImg, cvRGB, COLOR_BGR2RGB);
    cv_image<rgb_pixel> img1(cvRGB);

    cout << imgName << endl;
    int i = 1;
    for (auto face : detector(img1)) {
        auto shape = sp(img1, face);
        matrix<rgb_pixel> face_chip;
        // extract image from that shape, and scale it to 150x150px 
        extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
        // save face for further use
        faces.push_back(move(face_chip));
        face_graph->addFace(faces.back(), imageLocation, imgName);
    }
}
