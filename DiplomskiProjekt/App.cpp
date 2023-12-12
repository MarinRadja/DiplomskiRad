#include "App.h"



//#pragma region "Event Table"
//wxBEGIN_EVENT_TABLE(MyApp, wxApp)
//EVT_COMMAND(wxID_ANY, myEVT_CREATE_PROGRESS_WINDOW, MyApp::openProgressWindow)
//wxEND_EVENT_TABLE()
//#pragma endregion "Event Table"

bool MyApp::OnInit() {
#pragma region "Bind Events"
	Bind(myEVT_CREATE_PROGRESS_WINDOW,
		&MyApp::createProgressWindow,
		this,
		EventsIDs::CREATE_PROGRESS_WINDOW);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_detectedImage,
		this,
		EventsIDs::DETECTED_IMAGE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneDetectingImages,
		this,
		EventsIDs::DONE_DETECTING_IMAGES);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_detectedFace,
		this,
		EventsIDs::DETECTED_FACE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneDetectingFacesOnImage,
		this,
		EventsIDs::DONE_DETECTING_FACES_ON_IMAGE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneDetectingFaces,
		this,
		EventsIDs::DONE_DETECTING_FACES);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_comparedFace,
		this,
		EventsIDs::COMPARED_FACE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneComparingFaces,
		this,
		EventsIDs::DONE_COMPARING_FACES);

#pragma endregion "Bind Events"

	main_frame = new MainFrame("Face recognition");

	main_frame->SetClientSize(400, 300);
	main_frame->Center();

	main_frame->Show();

	return true;
}

#pragma region "Events"
#pragma region "Create windows events"
void MyApp::createProgressWindow(wxCommandEvent& evt) {
	if (progress_window != nullptr) progress_window->Destroy();

	progress_window = new ProgressWindow("Progress");

	progress_window->SetClientSize(400, 300);
	progress_window->Center();
	progress_window->Show();


	std::thread sw(&MyApp::startWorking, this, evt.GetString().ToStdString());
	sw.detach();
}

void MyApp::createFaceClusterWindow(wxCommandEvent& event) {
	if (face_cluster_window != nullptr) face_cluster_window->Destroy();

	face_cluster_window = new FaceClusterWindow("Recognized faces", main_frame->getAlgorithmPtr()->getFaceGraph());

	face_cluster_window->SetClientSize(800, 600);
	face_cluster_window->Center();
	face_cluster_window->Show();
}
#pragma endregion

#pragma region "Update Progress Window"
void MyApp::updateProgressWindow_detectedImage(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->detectingImagesPlusOne();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_doneDetectingImages(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->finishedDetectingImages();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_detectedFace(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->detectingFacesPlusOne();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_doneDetectingFacesOnImage(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->detectingFacesGaugePlusOne();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_doneDetectingFaces(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->setComparingFacesRange(evt.GetInt());
	progress_window->finishedDetectingFaces();
	progress_window->Layout();
}

// not done
void MyApp::updateProgressWindow_comparedFace(wxCommandEvent& evt) {
	while (progress_window == nullptr);

}

void MyApp::updateProgressWindow_doneComparingFaces(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->finishedDetectingFaces();
	progress_window->Layout();
}
#pragma endregion

#pragma endregion

wxIMPLEMENT_APP(MyApp);

#pragma region "Thread"
void MyApp::startWorking(string folderLocation) {
	main_frame->getAlgorithmPtr()->runAlgorithm(folderLocation);
}
#pragma endregion