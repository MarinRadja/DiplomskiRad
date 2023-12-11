#include "ProgressWindow.h"

ProgressWindow::ProgressWindow(const wxString& title) 
	: wxFrame(nullptr, wxID_ANY, title), images_found(0), faces_found(0), faces_analyzed(0), images_analyzed(0) {

#pragma region "Binding Events"
	Bind(EVT_UPDATE_PROGRESS_WINDOW, 
		&ProgressWindow::detectingImagesPlusOne,
		this,
		ProgressWindowEventsIDs::DETECTED_IMAGE);

	Bind(EVT_UPDATE_PROGRESS_WINDOW, 
		&ProgressWindow::finishedDetectingImages,
		this,
		ProgressWindowEventsIDs::DONE_DETECTING_IMAGES);
#pragma endregion "Binding Events"

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxVERTICAL);

	createImagesFoundText(clientAreaSizer);
	createFindingFacesOnImagesProgress(clientAreaSizer);
	createClusteringFacesProgress(clientAreaSizer);

	SetSizerAndFit(clientAreaSizer);
	SetMinSize(wxSize(400, 300));
	Layout();

	::wxInitAllImageHandlers();
}

void ProgressWindow::createImagesFoundText(wxBoxSizer* parentSizer) {
	wxBoxSizer* imagesFoundSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* imagesFoundTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_IMAGE_TXT, detectingImages(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	imagesFoundSizer->Add(imagesFoundTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(imagesFoundSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer) {
	createDetectingFacesText(parentSizer);
	createDetectingFacesGauge(parentSizer);
}

void ProgressWindow::createClusteringFacesProgress(wxBoxSizer* parentSizer) {
	createClusteringFacesText(parentSizer);
	createClusteringFacesGauge(parentSizer);
}

void ProgressWindow::createDetectingFacesText(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesTxtSizer = new wxBoxSizer(wxHORIZONTAL); 
	wxStaticText* detectingFacesTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_FACE_TXT, detectingFaces(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	detectingFacesTxtSizer->Add(detectingFacesTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesTxtSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createDetectingFacesGauge(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesGaugeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxGauge* detectingFacesGauge = new wxGauge(this, ProgressWindowIDs::DETECTING_FACE_GAUGE, images_found);

	detectingFacesGaugeSizer->Add(detectingFacesGauge, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesGaugeSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createClusteringFacesText(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesTxtSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* detectingFacesTxt = new wxStaticText(this, ProgressWindowIDs::CLUSTERING_FACE_TXT, clusteringFaces(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	detectingFacesTxtSizer->Add(detectingFacesTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesTxtSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createClusteringFacesGauge(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesGaugeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxGauge* detectingFacesGauge = new wxGauge(this, ProgressWindowIDs::CLUSTERING_FACE_GAUGE, faces_found);

	detectingFacesGaugeSizer->Add(detectingFacesGauge, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesGaugeSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

std::string ProgressWindow::detectingImages() {
	return "Found " + std::to_string(images_found) + " images so far.";
}

std::string ProgressWindow::detectingImagesDone() {
	return "Done! Total of " + std::to_string(images_found) + " images have been found.";
}

std::string ProgressWindow::detectingFaces() {
	return "Detecting faces: " + std::to_string(faces_found);
}

std::string ProgressWindow::detectingFacesDone() {
	return "Done! Detected " + std::to_string(faces_found) + " faces.";
}

std::string ProgressWindow::clusteringFaces() {
	return "Clustering faces: " + std::to_string(faces_analyzed) + "/" + std::to_string(faces_found);
}

std::string ProgressWindow::clusteringFacesDone() {
	return "Done! Clustered faces into x clusters";
}

void ProgressWindow::setImagesFound(int x) {
	images_found = x;
	this->Update();
}

void ProgressWindow::setImagesAnalyzed(int x) {
	images_analyzed = x;
	wxGauge* detectingFacesGauge = static_cast<wxGauge*>(FindWindowById(ProgressWindowIDs::DETECTING_FACE_GAUGE));
	detectingFacesGauge->SetValue(images_analyzed);
	this->Update();
}

void ProgressWindow::setFacesFound(int x) {
	faces_found = x;
	this->Update();
}

void ProgressWindow::setFacesAnalyzed(int x) {
	faces_analyzed = x;
	wxGauge* detectingFacesGauge = static_cast<wxGauge*>(FindWindowById(ProgressWindowIDs::CLUSTERING_FACE_GAUGE));
	detectingFacesGauge->SetValue(faces_analyzed);
	this->Update();
}

void ProgressWindow::detectingImagesPlusOne(wxCommandEvent& event) {
	images_found++;
	this->Update();
}

void ProgressWindow::finishedDetectingImages(wxCommandEvent& event) {
	wxStaticText* imagesFoundTxt = static_cast<wxStaticText*>(FindWindowById(ProgressWindowIDs::DETECTING_IMAGE_TXT));
	imagesFoundTxt->SetLabelText(detectingImagesDone());
	this->Update();
}

