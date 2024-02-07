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

	parentSizer->Add(sidebarSizer, 0, wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createFaceClusterTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* faceNameBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* face_name_lbl = new wxStaticText(this, wxID_ANY, "Name: ", wxDefaultPosition, wxSize(50, -1), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	face_name_box = new wxTextCtrl(this, wxID_ANY, 
		face_graph->getClusterPtr(i_cluster)->getFacePtr(i_face)->face_name, wxDefaultPosition, 
		wxSize(150, -1), wxTE_CENTER | wxTE_NO_VSCROLL);

	faceNameBoxSizer->Add(face_name_lbl, 0, wxSHAPED | wxALIGN_BOTTOM | wxALIGN_RIGHT, 3);
	faceNameBoxSizer->Add(face_name_box, 1, wxEXPAND | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);
	parentSizer->Add(faceNameBoxSizer, 0, wxEXPAND | wxALIGN_BOTTOM, 3);
}

void FaceClusterWindow::createMiniFace(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxHORIZONTAL);
	faceImage = new ImagePanel(this);

	imagePanelSizer->Add(faceImage, 3, wxSHAPED | wxALIGN_CENTER, 3);
	parentSizer->Add(imagePanelSizer, 10, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createControlForCurrentCluster(wxBoxSizer* parentSizer) {
	wxBoxSizer* prevNextImgButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevImg = new wxButton(this, FaceClusterWindowIDs::PREV_IMG, "<", wxDefaultPosition, wxSize(30, 20));
	face_index_box = new wxTextCtrl(this, wxID_ANY,
		std::to_string(i_face) + "/" + std::to_string(face_graph->getClusterPtr(i_cluster)->getNFaces()), wxDefaultPosition,
		wxDefaultSize, wxTE_CENTER | wxTE_NO_VSCROLL | wxTE_READONLY | wxTE_MULTILINE);
	wxButton* nextImg = new wxButton(this, FaceClusterWindowIDs::NEXT_IMG, ">", wxDefaultPosition, wxSize(30, 20));

	prevNextImgButtonSizer->Add(prevImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(face_index_box, 1, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(nextImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
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

void FaceClusterWindow::createSaveGraphButton(wxBoxSizer* parentSizer) {

}

void FaceClusterWindow::displayCurrentImage() {
	FaceCluster* current_cluster = face_graph->getClusterPtr(i_cluster);
	Face* current_face = current_cluster->getFacePtr(i_face);

	face_name_box->Clear();
	face_name_box->AppendText(current_face->face_name);

	face_index_box->Clear();
	face_index_box->AppendText(std::to_string(i_face + 1) + "/" + std::to_string(current_cluster->getNFaces() + 1));

	bigImage->displayFace(current_face->getImageLocation());
	bigImage->Refresh();

	faceImage->displayFace(current_face->getFaceLocation());
	faceImage->Refresh();
}

void FaceClusterWindow::saveName() {
	face_graph->getClusterPtr(i_cluster)->getFacePtr(i_face)->face_name = face_name_box->GetLineText(0);
}

#pragma region "Events"

void FaceClusterWindow::showPrevFaceImage(wxCommandEvent& event) {
	saveName();
	i_face = (i_face - 1) % face_graph->getNFacesFromClusterAt(i_cluster);

	displayCurrentImage();
}

void FaceClusterWindow::showNextFaceImage(wxCommandEvent& event) {
	saveName();
	i_face = (i_face + 1) % face_graph->getNFacesFromClusterAt(i_cluster);

	displayCurrentImage();
}

void FaceClusterWindow::showPrevCluster(wxCommandEvent& event) {
	saveName();
	i_face = 0;
	i_cluster = (i_cluster - 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

void FaceClusterWindow::showNextCluster(wxCommandEvent& event) {
	saveName();
	i_face = 0;
	i_cluster = (i_cluster + 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

#pragma endregion "Events"