#include "FaceClusterWindow.h"

#pragma region "Event Table"
#pragma endregion "Event Table"

FaceClusterWindow::FaceClusterWindow(const wxString& title, FaceGraph* _face_graph)
	: wxFrame(nullptr, wxID_ANY, title) {

		Bind(wxEVT_BUTTON, &FaceClusterWindow::showPrevFaceImage, this, FaceClusterWindowIDs::PREV_IMG);
		Bind(wxEVT_BUTTON, &FaceClusterWindow::showNextFaceImage, this, FaceClusterWindowIDs::NEXT_IMG);
		Bind(wxEVT_BUTTON, &FaceClusterWindow::showPrevCluster, this, FaceClusterWindowIDs::PREV_CLUSTER);
		Bind(wxEVT_BUTTON, &FaceClusterWindow::showNextCluster, this, FaceClusterWindowIDs::NEXT_CLUSTER);
		Bind(wxEVT_FILEPICKER_CHANGED, &FaceClusterWindow::saveGraphToDisk, this, FaceClusterWindowIDs::SAVE_GRAPH);

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

	createFaceSection(sidebarSizer);
	createHorizontalLine(sidebarSizer, -1);
	createClusterSection(sidebarSizer);

	createSaveGraphButton(sidebarSizer);

	parentSizer->Add(sidebarSizer, 0, wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createFaceSection(wxBoxSizer* parentSizer) {
	createFaceTitle(parentSizer);
	parentSizer->AddSpacer(5);
	createMiniFace(parentSizer);
	parentSizer->AddSpacer(5);
	createSelectedFaceBox(parentSizer);
	parentSizer->AddSpacer(5);
	createFaceControlButtons(parentSizer);
}

void FaceClusterWindow::createClusterSection(wxBoxSizer* parentSizer) {
	createClusterTitle(parentSizer);
	parentSizer->AddSpacer(5);
	createMiniClusters(parentSizer);
	parentSizer->AddSpacer(5);
	createSelectedClusterBox(parentSizer);
	parentSizer->AddSpacer(5);
	createClusterButtons(parentSizer);
}

void FaceClusterWindow::createFaceTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* faceNameBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* face_name_lbl = new wxStaticText(this, wxID_ANY, "Slika: ", wxDefaultPosition, wxSize(100, -1), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	face_name_box = new wxTextCtrl(this, wxID_ANY, 
		"", wxDefaultPosition,
		wxSize(150, -1), wxTE_CENTER | wxTE_NO_VSCROLL);

	faceNameBoxSizer->Add(face_name_lbl, 0, wxSHAPED | wxALIGN_BOTTOM | wxALIGN_RIGHT, 3);
	faceNameBoxSizer->Add(face_name_box, 1, wxEXPAND | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);
	parentSizer->Add(faceNameBoxSizer, 1, wxEXPAND | wxALIGN_BOTTOM, 3);
}

void FaceClusterWindow::createMiniFace(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxHORIZONTAL);
	faceImage = new ImagePanel(this);

	imagePanelSizer->Add(faceImage, 3, wxSHAPED | wxALIGN_CENTER, 3);
	parentSizer->Add(imagePanelSizer, 10, wxSHAPED | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createSelectedFaceBox(wxBoxSizer* parentSizer) {
	face_selected_box = new wxCheckBox(this, wxID_ANY, "Slika odabrana: ", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE | wxALIGN_RIGHT);
	parentSizer->Add(face_selected_box, 0, wxALIGN_CENTER);
}

void FaceClusterWindow::createFaceControlButtons(wxBoxSizer* parentSizer) {
	wxBoxSizer* prevNextImgButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevImg = new wxButton(this, FaceClusterWindowIDs::PREV_IMG, "<", wxDefaultPosition, wxSize(75, -1));
	face_index_box = new wxStaticText(this, wxID_ANY,
		"", wxDefaultPosition,
		wxSize(150, -1), wxALIGN_CENTER);
	wxButton* nextImg = new wxButton(this, FaceClusterWindowIDs::NEXT_IMG, ">", wxDefaultPosition, wxSize(75, -1));

	prevNextImgButtonSizer->Add(prevImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(face_index_box, 1, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(nextImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(prevNextImgButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createClusterTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* faceNameBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cluster_name_lbl = new wxStaticText(this, wxID_ANY, "Osoba: ", wxDefaultPosition, wxSize(100, -1), wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	cluster_name_box = new wxTextCtrl(this, wxID_ANY,
		"", wxDefaultPosition,
		wxDefaultSize, wxTE_CENTER | wxTE_NO_VSCROLL);

	faceNameBoxSizer->Add(cluster_name_lbl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 3);
	faceNameBoxSizer->Add(cluster_name_box, 1, wxEXPAND | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);
	parentSizer->Add(faceNameBoxSizer, 1, wxEXPAND | wxALIGN_BOTTOM, 3);
}

void FaceClusterWindow::createMiniClusters(wxBoxSizer* parentSizer) {}

void FaceClusterWindow::createSelectedClusterBox(wxBoxSizer* parentSizer) {
	cluster_selected_box = new wxCheckBox(this, wxID_ANY, "Osoba odabrana: ", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE | wxALIGN_RIGHT);
	parentSizer->Add(cluster_selected_box, 0, wxALIGN_CENTER);
}

void FaceClusterWindow::createClusterButtons(wxBoxSizer* parentSizer) {
	wxBoxSizer* clusterButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevClusterButton = new wxButton(this, FaceClusterWindowIDs::PREV_CLUSTER,
		"<", wxDefaultPosition, wxSize(75, -1));
	cluster_index_box = new wxStaticText(this, wxID_ANY,
		"", wxDefaultPosition,
		wxSize(150, -1), wxALIGN_CENTER);
	wxButton* nextClusterButton = new wxButton(this, FaceClusterWindowIDs::NEXT_CLUSTER,
		">", wxDefaultPosition, wxSize(75, -1));

	clusterButtonSizer->Add(prevClusterButton, 0, wxEXPAND | wxALIGN_CENTER, 3);
	clusterButtonSizer->Add(cluster_index_box, 1, wxEXPAND | wxALIGN_CENTER, 3);
	clusterButtonSizer->Add(nextClusterButton, 0, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(clusterButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createOpenImgLocationButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* openImgLocationButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* openImgLocationButton = new wxButton(this, FaceClusterWindowIDs::OPEN_IMG_LOC, "Open image location", wxDefaultPosition, wxDefaultSize);

	openImgLocationButtonSizer->Add(openImgLocationButton, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(openImgLocationButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createSaveGraphButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* saveGraphSizer = new wxBoxSizer(wxHORIZONTAL);
	save_graph = new wxFilePickerCtrl(this, FaceClusterWindowIDs::SAVE_GRAPH,
		"/", "", "*.json", wxDefaultPosition, wxSize(-1, 30), wxFLP_SAVE | wxFLP_OVERWRITE_PROMPT);


	saveGraphSizer->Add(new wxStaticText(this, wxID_ANY, "Spremi prikaz: ", wxDefaultPosition, 
		wxSize(100, -1), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL),
			0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	saveGraphSizer->Add(save_graph, 1, wxEXPAND);
	parentSizer->Add(saveGraphSizer, 0, wxEXPAND | wxALIGN_BOTTOM, 5);
}


// figure out adding static line to sizer
void FaceClusterWindow::createHorizontalLine(wxBoxSizer* parentSizer, int y_size) {
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* info = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(30, y_size), wxALIGN_CENTER);

	infoSizer->Add(info, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(infoSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
	/*wxBoxSizer* horizontalLineSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticLine horizontalLine = new wxStaticLine(, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

	horizontalLineSizer->Add(horizontalLine, 1, wxALL | wxALIGN_LEFT | wxSHAPED);
	parentSizer->Add(horizontalLineSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);*/
}



void FaceClusterWindow::displayCurrentImage() {
	FaceCluster* current_cluster = face_graph->getClusterPtr(i_cluster);
	Face* current_face = current_cluster->getFacePtr(i_face);

	face_name_box->Clear();
	if (current_face->face_name.length() > 0)
		face_name_box->AppendText(current_face->face_name);

	cluster_name_box->Clear();
	if (current_cluster->cluster_name.length() > 0)
		cluster_name_box->AppendText(current_cluster->cluster_name);

	face_index_box->SetLabelText(std::to_string(i_face + 1) + "/" + std::to_string(current_cluster->getNFaces()));
	cluster_index_box->SetLabelText(std::to_string(i_cluster + 1) + "/" + std::to_string(face_graph->getNumberOfClusters()));

	face_selected_box->SetValue(current_face->selected);
	cluster_selected_box->SetValue(current_cluster->selected);

	bigImage->displayFace(current_face->getImageLocation());
	bigImage->Refresh();

	faceImage->displayFace(current_face->getFaceLocation());
	faceImage->Refresh();
}

void FaceClusterWindow::saveCurrent() {
	FaceCluster* currentCluster = face_graph->getClusterPtr(i_cluster);
	Face* currentFace = currentCluster->getFacePtr(i_face);

	currentFace->face_name = face_name_box->GetLineText(0);
	currentFace->selected = face_selected_box->GetValue();
	currentCluster->cluster_name = cluster_name_box->GetLineText(0);
	currentCluster->selected = cluster_selected_box->GetValue();
}

#pragma region "Events"

void FaceClusterWindow::showPrevFaceImage(wxCommandEvent& event) {
	saveCurrent();

	i_face = mod<int>(i_face - 1, face_graph->getNFacesFromClusterAt(i_cluster));

	displayCurrentImage();
}

void FaceClusterWindow::showNextFaceImage(wxCommandEvent& event) {
	saveCurrent();

	i_face = (i_face + 1) % face_graph->getNFacesFromClusterAt(i_cluster);

	displayCurrentImage();
}

void FaceClusterWindow::showPrevCluster(wxCommandEvent& event) {
	saveCurrent();

	i_face = 0;

	i_cluster = mod<int>(i_cluster - 1, face_graph->getNumberOfClusters());

	displayCurrentImage();
}

void FaceClusterWindow::showNextCluster(wxCommandEvent& event) {
	saveCurrent();

	i_face = 0;
	i_cluster = (i_cluster + 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

void FaceClusterWindow::saveGraphToDisk(wxFileDirPickerEvent& evt) {
	saveCurrent();

	std::string p = save_graph->GetPath().ToStdString();
	face_graph->saveGraphToJson(p);
}

#pragma endregion "Events"