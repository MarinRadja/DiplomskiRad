#include "FaceClusterWindow.h"

#pragma region "Event Table"
wxBEGIN_EVENT_TABLE(FaceClusterWindow, wxFrame)
EVT_BUTTON(FaceClusterWindowIDs::PREV_IMG, FaceClusterWindow::showPrevFaceImage)
EVT_BUTTON(FaceClusterWindowIDs::NEXT_IMG, FaceClusterWindow::showNextFaceImage)
EVT_BUTTON(FaceClusterWindowIDs::PREV_CLUSTER, FaceClusterWindow::showPrevCluster)
EVT_BUTTON(FaceClusterWindowIDs::NEXT_CLUSTER, FaceClusterWindow::showNextCluster)
wxEND_EVENT_TABLE()
#pragma endregion "Event Table"

FaceClusterWindow::FaceClusterWindow(const wxString& title, FaceGraph* _face_graph)
	: wxFrame(nullptr, wxID_ANY, title) {
		face_graph = _face_graph;
		if (face_graph->getNumberOfClusters() < 1) return;

		wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxHORIZONTAL);

		createImagePanel(clientAreaSizer);
		createSidebar(clientAreaSizer);

		SetSizerAndFit(clientAreaSizer);
		SetMinSize(wxSize(800, 600));
		Layout();

		::wxInitAllImageHandlers();

		displayCurrentImage();
}

void FaceClusterWindow::createImagePanel(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxVERTICAL);
	bigImage = new ImagePanel(this);

	imagePanelSizer->Add(bigImage, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(imagePanelSizer, 4, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createSidebar(wxBoxSizer* parentSizer) {
	wxBoxSizer* sidebarSizer = new wxBoxSizer(wxVERTICAL);

	createFaceClusterTitle(sidebarSizer);
	createMiniFace(sidebarSizer);
	createControlForCurrentCluster(sidebarSizer);
	createHorizontalLine(sidebarSizer);
	createOpenImgLocationButton(sidebarSizer);
	createHorizontalLine(sidebarSizer);
	createPrevFaceClusterButton(sidebarSizer);
	createNextFaceClusterButton(sidebarSizer);

	parentSizer->Add(sidebarSizer, 1, wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createFaceClusterTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* info = new wxStaticText(this, wxID_ANY, "Scroll through images of this face", wxDefaultPosition, wxSize(30, -1), wxALIGN_CENTER);

	infoSizer->Add(info, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(infoSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createMiniFace(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxHORIZONTAL);
	faceImage = new ImagePanel(this);

	imagePanelSizer->Add(faceImage, 3, wxSHAPED | wxALIGN_CENTER, 3);
	parentSizer->Add(imagePanelSizer, 10, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createControlForCurrentCluster(wxBoxSizer* parentSizer) {
	wxBoxSizer* prevNextImgButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevImg = new wxButton(this, FaceClusterWindowIDs::PREV_IMG, "<", wxDefaultPosition, wxDefaultSize);
	wxButton* nextImg = new wxButton(this, FaceClusterWindowIDs::NEXT_IMG, ">", wxDefaultPosition, wxDefaultSize);

	prevNextImgButtonSizer->Add(prevImg, 1, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(nextImg, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(prevNextImgButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

// figure out adding static line to sizer
void FaceClusterWindow::createHorizontalLine(wxBoxSizer* parentSizer) {
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* info = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(30, -1), wxALIGN_CENTER);

	infoSizer->Add(info, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(infoSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
	/*wxBoxSizer* horizontalLineSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticLine horizontalLine = new wxStaticLine(, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

	horizontalLineSizer->Add(horizontalLine, 1, wxALL | wxALIGN_LEFT | wxSHAPED);
	parentSizer->Add(horizontalLineSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);*/
}

void FaceClusterWindow::createOpenImgLocationButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* openImgLocationButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* openImgLocationButton = new wxButton(this, FaceClusterWindowIDs::OPEN_IMG_LOC, "Open image location", wxDefaultPosition, wxDefaultSize);

	openImgLocationButtonSizer->Add(openImgLocationButton, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(openImgLocationButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createPrevFaceClusterButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* nextClusterButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* nextClusterButton = new wxButton(this, FaceClusterWindowIDs::PREV_CLUSTER, "Previous group of faces", wxDefaultPosition, wxDefaultSize);

	nextClusterButtonSizer->Add(nextClusterButton, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(nextClusterButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createNextFaceClusterButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* prevClusterButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevClusterButton = new wxButton(this, FaceClusterWindowIDs::NEXT_CLUSTER, "Next group of faces", wxDefaultPosition, wxDefaultSize);

	prevClusterButtonSizer->Add(prevClusterButton, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(prevClusterButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::displayCurrentImage() {
	bigImage->displayFace(face_graph->getClusterPtr(i_cluster)->getFacePtr(i_face)->getImageLocation());
	bigImage->Refresh();

	faceImage->displayFace(face_graph->getClusterPtr(i_cluster)->getFacePtr(i_face)->getFaceLocation());
	faceImage->Refresh();
}


#pragma region "Events"

void FaceClusterWindow::showPrevFaceImage(wxCommandEvent& event) {
	i_face = (i_face - 1) % face_graph->getClusterPtr(i_cluster)->getNFaces();

	displayCurrentImage();
}

void FaceClusterWindow::showNextFaceImage(wxCommandEvent& event) {
	i_face = (i_face + 1) % face_graph->getClusterPtr(i_cluster)->getNFaces();

	displayCurrentImage();
}

void FaceClusterWindow::showPrevCluster(wxCommandEvent& event) {
	i_face = 0;
	i_cluster = (i_cluster - 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

void FaceClusterWindow::showNextCluster(wxCommandEvent& event) {
	i_face = 0;
	i_cluster = (i_cluster + 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

#pragma endregion "Events"