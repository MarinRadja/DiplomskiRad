#include "ProgressWindow.h"

ProgressWindow::ProgressWindow(const wxString& title) 
	: wxFrame(nullptr, wxID_ANY, title), images_found(0), faces_found(0), faces_analyzed(0), images_analyzed(0) {

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
	imagesFoundTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_IMAGE_TXT, detectingImages(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	imagesFoundSizer->Add(imagesFoundTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(imagesFoundSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer) {
	createDetectingFacesText(parentSizer);
	createDetectingFacesGauge(parentSizer);
}

void ProgressWindow::createClusteringFacesProgress(wxBoxSizer* parentSizer) {
	createComparingFacesText(parentSizer);
	createComparingFacesGauge(parentSizer);
}

void ProgressWindow::createDetectingFacesText(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesTxtSizer = new wxBoxSizer(wxHORIZONTAL); 
	detectingFacesTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_FACE_TXT, detectingFaces(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	detectingFacesTxtSizer->Add(detectingFacesTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesTxtSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createDetectingFacesGauge(wxBoxSizer* parentSizer) {
	wxBoxSizer* detectingFacesGaugeSizer = new wxBoxSizer(wxHORIZONTAL);
	detectingFacesGauge = new wxGauge(this, ProgressWindowIDs::DETECTING_FACE_GAUGE, images_found);

	detectingFacesGaugeSizer->Add(detectingFacesGauge, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(detectingFacesGaugeSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createComparingFacesText(wxBoxSizer* parentSizer) {
	wxBoxSizer* clusteringFacesTxtSizer = new wxBoxSizer(wxHORIZONTAL);
	comparingFacesTxt = new wxStaticText(this, ProgressWindowIDs::COMPARING_FACE_TXT, comparingFaces(), wxDefaultPosition, wxSize(150, 40), wxALIGN_CENTER);

	clusteringFacesTxtSizer->Add(comparingFacesTxt, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(clusteringFacesTxtSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void ProgressWindow::createComparingFacesGauge(wxBoxSizer* parentSizer) {
	wxBoxSizer* clusteringFacesGaugeSizer = new wxBoxSizer(wxHORIZONTAL);
	comparingFacesGauge = new wxGauge(this, ProgressWindowIDs::COMPARING_FACE_GAUGE, faces_found);

	clusteringFacesGaugeSizer->Add(comparingFacesGauge, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(clusteringFacesGaugeSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

std::string ProgressWindow::detectingImages() {
	return "Found " + std::to_string(images_found) + " images so far.";
}

std::string ProgressWindow::detectingImagesDone() {
	return "Done! Total of " + std::to_string(images_found) + " images have been found.";
}

std::string ProgressWindow::detectingFaces() {
	return "Scanning images for faces: " + std::to_string(faces_found) + " faces detected";
}

std::string ProgressWindow::detectingFacesDone() {
	return "Done! Detected " + std::to_string(faces_found) + " faces.";
}

std::string ProgressWindow::comparingFaces() {
	return "Clustering faces: " + std::to_string(faces_analyzed) + "/" + std::to_string(faces_found);
}

std::string ProgressWindow::comparingFacesDone() {
	return "Done! Clustered faces into x clusters";
}

std::string ProgressWindow::clusteringFaces() {
	return "Clustering faces: " + std::to_string(faces_analyzed) + "/" + std::to_string(faces_found);
}

std::string ProgressWindow::clusteringFacesDone() {
	return "Done! Clustered faces into x clusters";
}

void ProgressWindow::setImagesFound(int x) {
	images_found = x; 
}

void ProgressWindow::setImagesAnalyzed(int x) {
	images_analyzed = x;
	detectingFacesGauge->SetValue(images_analyzed);
}

void ProgressWindow::setFacesFound(int x) {
	faces_found = x;
}

void ProgressWindow::setFacesAnalyzed(int x) {
	faces_analyzed = x;
	detectingFacesGauge->SetValue(faces_analyzed);
}

void ProgressWindow::detectingImagesPlusOne() {
	images_found++;
	imagesFoundTxt->SetLabelText(detectingImages());
}

void ProgressWindow::finishedDetectingImages() {
	imagesFoundTxt->SetLabelText(detectingImagesDone());
	detectingFacesGauge->SetRange(images_found);
}

void ProgressWindow::detectingFacesPlusOne() {
	faces_found++;
	detectingFacesTxt->SetLabelText(detectingFaces());
}

void ProgressWindow::detectingFacesGaugePlusOne() {
	images_analyzed++;
	detectingFacesGauge->SetValue(images_analyzed);
}

void ProgressWindow::finishedDetectingFaces() {
	detectingFacesTxt->SetLabelText(detectingFacesDone());
}

void ProgressWindow::setComparingFacesRange(int r) {
	comparingFacesGauge->SetRange(r);
}
