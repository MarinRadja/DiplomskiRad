#include "App.h"



//#pragma region "Event Table"
//wxBEGIN_EVENT_TABLE(App, wxApp)
//EVT_COMMAND(wxID_ANY, EVT_SHOW_PROGRESS_WINDOW, App::openProgressWindow)
//wxEND_EVENT_TABLE()
//#pragma endregion "Event Table"

bool App::OnInit() {
#pragma region "Binding Events"
	this->Bind(EVT_UPDATE_PROGRESS_WINDOW,
		&App::createFaceClusterWindow,
		ProgressWindowEventsIDs::DONE_CLUSTERING_FACES);

#pragma endregion "Binding Events"

	main_frame = new MainFrame("Face recognition");

	main_frame->SetClientSize(400, 300);
	main_frame->Center();

	main_frame->Show();
	return true;
}

void App::createProgressWindow(wxCommandEvent& event) {
	ProgressWindow* progressWindow = new ProgressWindow("Progress");
	progressWindow->SetClientSize(400, 300);
	progressWindow->Center();

	progressWindow->Show();
}

void App::createFaceClusterWindow(wxCommandEvent& event) {
	FaceClusterWindow* faceClusterWindow = new FaceClusterWindow("Recognized faces", main_frame->getAlgorithmPtr()->getFaceGraph());
	faceClusterWindow->SetClientSize(800, 600);
	faceClusterWindow->Center();

	faceClusterWindow->Show();
}

wxIMPLEMENT_APP(App);
