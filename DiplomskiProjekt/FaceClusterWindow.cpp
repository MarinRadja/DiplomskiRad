#include "FaceClusterWindow.h"

#pragma region "Event Table"
#pragma endregion "Event Table"

FaceClusterWindow::FaceClusterWindow(const wxString& title, FaceGraph* _face_graph, bool canSearch)
	: wxFrame(nullptr, wxID_ANY, title) {

	can_search = canSearch;

	Bind(wxEVT_BUTTON, &FaceClusterWindow::showPrevFaceImage, this, FaceClusterWindowIDs::PREV_IMG);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::showNextFaceImage, this, FaceClusterWindowIDs::NEXT_IMG);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::showPrevCluster, this, FaceClusterWindowIDs::PREV_CLUSTER);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::showNextCluster, this, FaceClusterWindowIDs::NEXT_CLUSTER);

	Bind(wxEVT_CHECKBOX, &FaceClusterWindow::selectedFace, this, FaceClusterWindowIDs::FACE_CHECKBOX);
	Bind(wxEVT_CHECKBOX, &FaceClusterWindow::selectedCluster, this, FaceClusterWindowIDs::CLUSTER_CHECKBOX);

	Bind(wxEVT_BUTTON, &FaceClusterWindow::removeCurrentImage, this, FaceClusterWindowIDs::REMOVE_CURRENT_IMAGE);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::removeCurrentPerson, this, FaceClusterWindowIDs::REMOVE_CURRENT_PERSON);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::removeSelected, this, FaceClusterWindowIDs::REMOVE_SELECTED);
	Bind(wxEVT_BUTTON, &FaceClusterWindow::removeNonSelected, this, FaceClusterWindowIDs::REMOVE_NON_SELECTED);

	Bind(wxEVT_FILEPICKER_CHANGED, &FaceClusterWindow::saveGraphToDisk, this, FaceClusterWindowIDs::SAVE_GRAPH);

	face_graph = _face_graph;
	if (face_graph->getNumberOfClusters() < 1) return;

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	createImagePanel(clientAreaSizer);
	createSidebar(clientAreaSizer);

	SetSizerAndFit(clientAreaSizer);
	SetMinSize(wxSize(800, 600));
	displayCurrentImage();
	Layout();

	::wxInitAllImageHandlers();

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
	sidebarSizer->AddSpacer(20);
	createClusterSection(sidebarSizer);
	sidebarSizer->AddSpacer(15);
	createDropSection(sidebarSizer);
	sidebarSizer->AddSpacer(15);
	createSaveGraphSection(sidebarSizer);
	sidebarSizer->AddSpacer(10);
	createSearchPeopleSection(sidebarSizer);

	parentSizer->Add(sidebarSizer, 0, wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createFaceSection(wxBoxSizer* parentSizer) {
	createFaceTitle(parentSizer);
	parentSizer->AddSpacer(5);
	createSelectedFaceBox(parentSizer);
	parentSizer->AddSpacer(5);
	createFaceControlButtons(parentSizer);
}

void FaceClusterWindow::createClusterSection(wxBoxSizer* parentSizer) {
	createClusterTitle(parentSizer);
	parentSizer->AddSpacer(5);
	createMiniFace(parentSizer);
	parentSizer->AddSpacer(5);
	createSelectedClusterBox(parentSizer);
	parentSizer->AddSpacer(5);
	createClusterButtons(parentSizer);
}

void FaceClusterWindow::createDropSection(wxBoxSizer* parentSizer) {
	parentSizer->Add(new wxStaticText(this, wxID_ANY, "Izbaci:", wxDefaultPosition, wxDefaultSize, wxTE_CENTER),
		0, wxEXPAND);

	wxBoxSizer* dropCurrentButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	dropCurrentButtonsSizer->Add(new wxButton(this, FaceClusterWindowIDs::REMOVE_CURRENT_IMAGE, "Trenutnu sliku", wxDefaultPosition, wxSize(100, -1)),
		1, wxEXPAND);
	dropCurrentButtonsSizer->Add(new wxButton(this, FaceClusterWindowIDs::REMOVE_CURRENT_PERSON, "Trenutnu osobu", wxDefaultPosition, wxSize(100, -1)), 
		1, wxEXPAND);
		
	wxBoxSizer* dropSelectedButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	dropSelectedButtonsSizer->Add(new wxButton(this, FaceClusterWindowIDs::REMOVE_SELECTED, "Odabrano", wxDefaultPosition, wxSize(100, -1)),
		1, wxEXPAND);
	dropSelectedButtonsSizer->Add(new wxButton(this, FaceClusterWindowIDs::REMOVE_NON_SELECTED, "Ne odabrano", wxDefaultPosition, wxSize(100, -1)),
		1, wxEXPAND);
	
	parentSizer->Add(dropCurrentButtonsSizer, 0, wxALIGN_CENTER);
	parentSizer->AddSpacer(2);
	parentSizer->Add(dropSelectedButtonsSizer, 0, wxALIGN_CENTER);
}

void FaceClusterWindow::createSaveGraphSection(wxBoxSizer* parentSizer) {
	createSaveGraphSectionToggles(parentSizer);
	createSaveGraphButton(parentSizer);
}

void FaceClusterWindow::createFaceTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* faceNameBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* face_name_lbl = new wxStaticText(this, wxID_ANY, "Slika: ", wxDefaultPosition, wxSize(100, -1), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	face_name_box = new wxTextCtrl(this, wxID_ANY, 
		"", wxDefaultPosition,
		wxSize(150, -1), wxTE_CENTER | wxTE_NO_VSCROLL);

	faceNameBoxSizer->Add(face_name_lbl, 0, wxSHAPED | wxALIGN_BOTTOM | wxALIGN_RIGHT, 3);
	faceNameBoxSizer->Add(face_name_box, 1, wxSHAPED | wxALIGN_LEFT | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);
	parentSizer->Add(faceNameBoxSizer, 1, wxEXPAND | wxALIGN_BOTTOM, 3);
}

void FaceClusterWindow::createMiniFace(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxHORIZONTAL);
	faceImage = new ImagePanel(this);

	imagePanelSizer->Add(faceImage, 3, wxSHAPED | wxALIGN_CENTER, 3);
	parentSizer->Add(imagePanelSizer, 10, wxSHAPED | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createSelectedFaceBox(wxBoxSizer* parentSizer) {
	face_selected_box = new wxCheckBox(this, FaceClusterWindowIDs::FACE_CHECKBOX, "Slika odabrana: ", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE | wxALIGN_RIGHT);
	parentSizer->Add(face_selected_box, 0, wxALIGN_CENTER);
}

void FaceClusterWindow::createFaceControlButtons(wxBoxSizer* parentSizer) {
	wxBoxSizer* prevNextImgButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* prevImg = new wxButton(this, FaceClusterWindowIDs::PREV_IMG, "<", wxDefaultPosition, wxSize(75, -1));
	face_index_box = new wxStaticText(this, wxID_ANY,
		"", wxDefaultPosition,
		wxSize(150, -1), wxALIGN_CENTER);
	wxButton* nextImg = new wxButton(this, FaceClusterWindowIDs::NEXT_IMG, ">", wxDefaultPosition, wxSize(75, -1));

	prevNextImgButtonSizer->AddSpacer(15);
	prevNextImgButtonSizer->Add(prevImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(face_index_box, 1, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->Add(nextImg, 0, wxEXPAND | wxALIGN_CENTER, 3);
	prevNextImgButtonSizer->AddSpacer(15);
	parentSizer->Add(prevNextImgButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createClusterTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* faceNameBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cluster_name_lbl = new wxStaticText(this, wxID_ANY, "Osoba: ", wxDefaultPosition, wxSize(100, -1), wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	cluster_name_box = new wxTextCtrl(this, wxID_ANY,
		"", wxDefaultPosition,
		wxSize(150, -1), wxTE_CENTER | wxTE_NO_VSCROLL);

	faceNameBoxSizer->Add(cluster_name_lbl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 3);
	faceNameBoxSizer->Add(cluster_name_box, 1, wxSHAPED | wxALIGN_LEFT | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);
	parentSizer->Add(faceNameBoxSizer, 1, wxEXPAND | wxALIGN_BOTTOM, 3);
}

void FaceClusterWindow::createMiniClusters(wxBoxSizer* parentSizer) {}

void FaceClusterWindow::createSelectedClusterBox(wxBoxSizer* parentSizer) {
	cluster_selected_box = new wxCheckBox(this, FaceClusterWindowIDs::CLUSTER_CHECKBOX, "Osoba odabrana: ", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE | wxALIGN_RIGHT);
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

	clusterButtonSizer->AddSpacer(15);
	clusterButtonSizer->Add(prevClusterButton, 0, wxEXPAND | wxALIGN_CENTER, 3);
	clusterButtonSizer->Add(cluster_index_box, 1, wxEXPAND | wxALIGN_CENTER, 3);
	clusterButtonSizer->Add(nextClusterButton, 0, wxEXPAND | wxALIGN_CENTER, 3);
	clusterButtonSizer->AddSpacer(15);
	parentSizer->Add(clusterButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createOpenImgLocationButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* openImgLocationButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* openImgLocationButton = new wxButton(this, FaceClusterWindowIDs::OPEN_IMG_LOC, "Open image location", wxDefaultPosition, wxDefaultSize);

	openImgLocationButtonSizer->Add(openImgLocationButton, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(openImgLocationButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void FaceClusterWindow::createSaveGraphSectionToggles(wxBoxSizer* parentSizer) {
	wxBoxSizer* saveToggleSizer = new wxBoxSizer(wxHORIZONTAL);
}

void FaceClusterWindow::createSaveGraphButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* saveGraphSizer = new wxBoxSizer(wxHORIZONTAL);
	save_graph = new wxFilePickerCtrl(this, FaceClusterWindowIDs::SAVE_GRAPH,
		"/", "", "*.json", wxDefaultPosition, wxSize(150, 30), wxFLP_SAVE | wxFLP_OVERWRITE_PROMPT);


	saveGraphSizer->AddSpacer(15);
	saveGraphSizer->Add(new wxStaticText(this, wxID_ANY, "Spremi prikaz: ", wxDefaultPosition, 
		wxSize(100, -1), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL),
			0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	saveGraphSizer->Add(save_graph, 1, wxSHAPED | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	parentSizer->Add(saveGraphSizer, 0, wxEXPAND | wxALIGN_BOTTOM, 5);
}

void FaceClusterWindow::createSearchPeopleSection(wxBoxSizer* parentSizer) {
	wxBoxSizer* searchPeopleSizer = new wxBoxSizer(wxHORIZONTAL);
	search_people = new wxFilePickerCtrl(this, FaceClusterWindowIDs::SEARCH_PEOPLE,
		"/", "", "*.jpeg", wxDefaultPosition, wxSize(150, 30), wxFLP_FILE_MUST_EXIST | wxFLP_OPEN);

	if (!can_search)
		search_people->Disable();

	searchPeopleSizer->AddSpacer(15);
	searchPeopleSizer->Add(new wxStaticText(this, wxID_ANY, "Potraži u prikazu: ", wxDefaultPosition,
		wxSize(100, -1), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL),
		0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	searchPeopleSizer->Add(search_people, 1, wxSHAPED | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	parentSizer->Add(searchPeopleSizer, 0, wxEXPAND | wxALIGN_BOTTOM, 5);
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
	face_name_box->Clear();
	cluster_name_box->Clear();

	if (face_graph->getNumberOfClusters() == 0) {
		bigImage->Destroy();
		faceImage->Destroy();
		face_index_box->SetLabelText("0/0");
		cluster_index_box->SetLabelText("0/0");
		return;
	}

	FaceCluster* current_cluster = face_graph->getClusterPtr(i_cluster);
	Face* current_face = current_cluster->getFacePtr(i_face);

	if (current_face->face_name.length() > 0)
		face_name_box->AppendText(current_face->face_name);

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

void FaceClusterWindow::removeIfMatches(bool isSelected) {
	saveCurrent();

	i_face = 0;
	i_cluster = 0;

	face_graph->removeIfSelectedMatches(isSelected);

	displayCurrentImage();
}

void FaceClusterWindow::updateAfterSearch() {
	i_face = 0;
	i_cluster = 0;
	displayCurrentImage();
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
	if (face_graph->getNumberOfClusters() == 0) return;
	saveCurrent();

	i_face = mod<int>(i_face - 1, face_graph->getNFacesFromClusterAt(i_cluster));

	displayCurrentImage();
}

void FaceClusterWindow::showNextFaceImage(wxCommandEvent& event) {
	if (face_graph->getNumberOfClusters() == 0) return;
	saveCurrent();

	i_face = (i_face + 1) % face_graph->getNFacesFromClusterAt(i_cluster);

	displayCurrentImage();
}

void FaceClusterWindow::showPrevCluster(wxCommandEvent& evt) {
	if (face_graph->getNumberOfClusters() == 0) return;
	saveCurrent();

	i_face = 0;

	i_cluster = mod<int>(i_cluster - 1, face_graph->getNumberOfClusters());

	displayCurrentImage();
}

void FaceClusterWindow::showNextCluster(wxCommandEvent& evt) {
	if (face_graph->getNumberOfClusters() == 0) return;
	saveCurrent();

	i_face = 0;
	i_cluster = (i_cluster + 1) % face_graph->getNumberOfClusters();

	displayCurrentImage();
}

void FaceClusterWindow::selectedFace(wxCommandEvent& evt) {
	saveCurrent();
	cluster_selected_box->SetValue(face_graph->getClusterPtr(i_cluster)->allSelected());
}

void FaceClusterWindow::selectedCluster(wxCommandEvent& evt) {
	face_graph->getClusterPtr(i_cluster)->selectAllFaces(cluster_selected_box->GetValue());
	face_selected_box->SetValue(cluster_selected_box->GetValue());
}

void FaceClusterWindow::removeCurrentImage(wxCommandEvent& evt) {
	if (face_graph->removeFace(i_face, i_cluster)) {
		i_cluster = mod<int>(i_cluster - 1, face_graph->getNumberOfClusters());
	}
	i_face = mod<int>(i_face - 1, face_graph->getNFacesFromClusterAt(i_cluster));
	displayCurrentImage();
}

void FaceClusterWindow::removeCurrentPerson(wxCommandEvent& evt) {
	face_graph->removeCluster(i_cluster);
	i_cluster = mod<int>(i_cluster - 1, face_graph->getNumberOfClusters());
	i_face = 0;
	displayCurrentImage();
}

void FaceClusterWindow::removeSelected(wxCommandEvent& evt) {
	removeIfMatches(true);
}

void FaceClusterWindow::removeNonSelected(wxCommandEvent& evt) {
	removeIfMatches(false);
}

void FaceClusterWindow::saveGraphToDisk(wxFileDirPickerEvent& evt) {
	saveCurrent();

	std::string p = save_graph->GetPath().ToStdString();
	face_graph->saveGraphToJson(p);
}

#pragma endregion "Events"