#include "FaceDetector.h"




FaceDetector::FaceDetector() {
    this->inWidth = 300;
    this->inHeight = 300;
    this->inScaleFactor = 1.0;
    this->confidenceThreshold = 0.7;
    this->meanVal = Scalar(104.0, 177.0, 123.0);

    // get face detector
    detector = get_frontal_face_detector();

    // load cnn face detector
    deserialize(face_detector_location) >> face_detector_net;

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

    // load cnn face detector
    deserialize(face_detector_location) >> face_detector_net;

    // load face shape detector
    deserialize(shape_predictor_location) >> sp;

    face_graph = _face_graph;
}

void FaceDetector::detectFaceOpenCVDNN(Mat& cvImg, string framework, string imgName, string imageLocation) {
    // convert opencv img format to dlib img format
    Mat cvRGB;
    cvtColor(cvImg, cvRGB, COLOR_BGR2RGB);
    cv_image<rgb_pixel> img1(cvRGB);
    matrix<rgb_pixel> ma;
    assign_image(ma, img1);

    // wxImage test(cvRGB.cols, cvRGB.rows, cvRGB.data, true);

    cout << imgName << endl;
    int i = 1;
    for (auto&& face : face_detector_net(ma)) {      // for each face found in img1
        auto shape = sp(img1, face.rect);        // find shape of the face
        matrix<rgb_pixel> face_chip;        
        // extract image from that shape, and scale it to 150x150px 
        extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
        // save face for further use
        faces.push_back(move(face_chip));
        face_graph->addFace(faces.back(), imageLocation, imgName);
        wxTheApp->QueueEvent(new wxCommandEvent(myEVT_UPDATE_PROGRESS_WINDOW, EventsIDs::DETECTED_FACE));


        // converting image format from dlib to opencv
        // and saving it to disk with opencv
        //Mat faceToSaveRGB(toMat(faces.at(faces.size() - 1)));
        //Mat faceToSaveBGR;
        //cvtColor(faceToSaveRGB, faceToSaveBGR, COLOR_RGB2BGR);
        //string whereToSave = "faces/" + imgName + "_" + to_string(i++) + ".jpg";
        //imwrite(whereToSave, faceToSaveBGR);
    }




    // further down is opencv implementation of face detection with dnn
    // switched to dlib face detection as facial features embedder was trained with dlib detector
    // might revisit in future


    /*

    int frameHeight = frameOpenCVDNN.rows;
    int frameWidth = frameOpenCVDNN.cols;

    Mat inputBlob;
    if (framework == "caffe")
        inputBlob = blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);
    else
        inputBlob = blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, true, false);

    net.setInput(inputBlob, "data");
    Mat detection = net.forward("detection_out");

    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    for (int i = 0; i < detectionMat.rows; i++)
    {
        float confidence = detectionMat.at<float>(i, 2);

        if (confidence > confidenceThreshold)
        {
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);

            Rect facePos(x1, y1, (x2 - x1), (y2 - y1));
            Mat face = frameOpenCVDNN(facePos);

            imwrite("E:/Programming/_Projects/DiplomskiProjekt/ImageSets/faces/" + imgName + "_" + to_string(i) + ".jpg", face);


            cout << "x1=" << x1 << "\ty1=" << y1 << "\tx2=" << x2 << "\ty2=" << y2 << endl;
            rectangle(frameOpenCVDNN, cv::Point(x1, y1), cv::Point(x2, y2),
                cv::Scalar((i == 0) ? 255 : 0, (i == 1) ? 255 : 0, (i == 2) ? 255 : 0), 2, 4);
        }
    }*/
}