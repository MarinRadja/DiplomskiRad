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
		&MyApp::updateProgressWindow_NNDone,
		this,
		EventsIDs::NN_DONE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_comparedFace,
		this,
		EventsIDs::COMPARED_FACE);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneComparingFaces,
		this,
		EventsIDs::DONE_COMPARING_FACES);

	Bind(myEVT_UPDATE_PROGRESS_WINDOW,
		&MyApp::updateProgressWindow_doneClusteringFaces,
		this,
		EventsIDs::DONE_CLUSTERING_FACES);

	Bind(myEVT_LOAD_GRAPH_FROM_DISK,
		&MyApp::loadGraphFromDisk,
		this,
		wxID_ANY);

#pragma endregion "Bind Events"

	createMainWindow();
	return true;
}

#pragma region "Events"
#pragma region "Create windows"
void MyApp::createMainWindow() {
	if (main_frame != nullptr) main_frame->Destroy();

	main_frame = new MainFrame("Face recognition");
	main_frame->SetClientSize(400, 300);
	main_frame->Center();
	main_frame->Show();
}

void MyApp::createProgressWindow(wxCommandEvent& evt) {
	if (progress_window != nullptr) progress_window->Destroy();

	progress_window = new ProgressWindow("Progress");
	progress_window->SetClientSize(400, 300);
	progress_window->Center();
	progress_window->Show();

	std::thread sw(&MyApp::startWorking, this, evt.GetString().ToStdString());
	sw.detach();
}

void MyApp::createFaceClusterWindow(FaceGraph* faceGraph) {
	if (face_cluster_window != nullptr) face_cluster_window->Destroy();

	face_cluster_window = new FaceClusterWindow("Recognized faces", faceGraph);
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

void MyApp::updateProgressWindow_NNDone(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->NNDone();
	progress_window->Layout();
}

// not done
void MyApp::updateProgressWindow_comparedFace(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->comparingFacesGougePlusOne();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_doneComparingFaces(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->finishedComparingFaces();
	progress_window->Layout();
}

void MyApp::updateProgressWindow_doneClusteringFaces(wxCommandEvent& evt) {
	while (progress_window == nullptr);
	progress_window->Destroy();
	createFaceClusterWindow(main_frame->getAlgorithmPtr()->getFaceGraph());
}

void MyApp::loadGraphFromDisk(wxCommandEvent& evt) {
	std::string jsonLoc = evt.GetString().ToStdString();

	face_graph.loadGraphFromJson(jsonLoc);

	main_frame->Hide();
	createFaceClusterWindow(&face_graph);
}
#pragma endregion

#pragma endregion

wxIMPLEMENT_APP(MyApp);

#pragma region "Thread"
void MyApp::startWorking(string folderLocation) {
	main_frame->getAlgorithmPtr()->runAlgorithm(folderLocation);
}
#pragma endregion