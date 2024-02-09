#include "ProgressWindow.h"

ProgressWindow::ProgressWindow(const wxString& title) 
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500), 
		wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), 
	images_found(0), faces_found(0), faces_analyzed(0), images_analyzed(0), faces_compared(0), total_comparisons(0) {

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxVERTICAL);

	clientAreaSizer->AddSpacer(10);
	createImagesFoundProgress(clientAreaSizer);
	createFindingFacesOnImagesProgress(clientAreaSizer);
	createNNProgress(clientAreaSizer);
	createClusteringFacesProgress(clientAreaSizer);
	clientAreaSizer->AddSpacer(5);

	SetSizerAndFit(clientAreaSizer);
	Center();
	Layout();
	Show();

	::wxInitAllImageHandlers();
}

void ProgressWindow::createImagesFoundProgress(wxBoxSizer* parentSizer) {
	createImagesFoundText(parentSizer);
	createImagesFoundGauge(parentSizer);
}

void ProgressWindow::createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer) {
	createDetectingFacesText(parentSizer);
	createDetectingFacesGauge(parentSizer);
}

void ProgressWindow::createNNProgress(wxBoxSizer* parentSizer) {
	createNNText(parentSizer);
	createNNGauge(parentSizer);
}

void ProgressWindow::createClusteringFacesProgress(wxBoxSizer* parentSizer) {
	createComparingFacesText(parentSizer);
	createComparingFacesGauge(parentSizer);
}

void ProgressWindow::createImagesFoundText(wxBoxSizer* parentSizer) {
	imagesFoundTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_IMAGE_TXT, detectingImages(), wxDefaultPosition, wxSize(500, -1), wxALIGN_CENTER);

	parentSizer->Add(imagesFoundTxt, 0, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(5);
}

void ProgressWindow::createImagesFoundGauge(wxBoxSizer* parentSizer) {
	detectingImagesGauge = new wxGauge(this, ProgressWindowIDs::DETECTING_FACE_GAUGE, 1);
	detectingImagesGauge->Pulse();

	parentSizer->Add(detectingImagesGauge, 1, wxEXPAND | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(10);
}

void ProgressWindow::createDetectingFacesText(wxBoxSizer* parentSizer) {
	detectingFacesTxt = new wxStaticText(this, ProgressWindowIDs::DETECTING_FACE_TXT, detectingFaces(), wxDefaultPosition, wxSize(500, -1), wxALIGN_CENTER);

	parentSizer->Add(detectingFacesTxt, 0, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(5);
}

void ProgressWindow::createDetectingFacesGauge(wxBoxSizer* parentSizer) {
	detectingFacesGauge = new wxGauge(this, ProgressWindowIDs::DETECTING_FACE_GAUGE, images_found);

	parentSizer->Add(detectingFacesGauge, 1, wxEXPAND | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(10);
}

void ProgressWindow::createNNText(wxBoxSizer* parentSizer) {
	NNTxt = new wxStaticText(this, wxID_ANY, "Waiting for faces to be detected.", wxDefaultPosition, wxSize(500, -1), wxALIGN_CENTER);

	parentSizer->Add(NNTxt, 0, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(5);
}

void ProgressWindow::createNNGauge(wxBoxSizer* parentSizer) {
	NNGauge = new wxGauge(this, wxID_ANY, 1);

	parentSizer->Add(NNGauge, 1, wxEXPAND | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(10);
}

void ProgressWindow::createComparingFacesText(wxBoxSizer* parentSizer) {
	comparingFacesTxt = new wxStaticText(this, ProgressWindowIDs::COMPARING_FACE_TXT, comparingFaces(), wxDefaultPosition, wxSize(500, -1), wxALIGN_CENTER);

	parentSizer->Add(comparingFacesTxt, 0, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);
	parentSizer->AddSpacer(5);
}

void ProgressWindow::createComparingFacesGauge(wxBoxSizer* parentSizer) {
	comparingFacesGauge = new wxGauge(this, ProgressWindowIDs::COMPARING_FACE_GAUGE, total_comparisons);

	parentSizer->Add(comparingFacesGauge, 1, wxEXPAND | wxALIGN_BOTTOM);
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
	return "Comparing faces: " + std::to_string(faces_compared) + "/" + std::to_string(total_comparisons);
}

std::string ProgressWindow::comparingFacesDone() {
	return "Done! Compared all faces.";
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

void ProgressWindow::detectingImagesPlusX(int x) {
	images_found += x;
	imagesFoundTxt->SetLabelText(detectingImages());
	detectingImagesGauge->Pulse();
}

void ProgressWindow::finishedDetectingImages() {
	imagesFoundTxt->SetLabelText(detectingImagesDone());
	detectingImagesGauge->SetValue(1);
	detectingFacesGauge->SetRange(images_found);
}

void ProgressWindow::detectingFacesPlusOne() {
	faces_found++;
	detectingFacesTxt->SetLabelText(detectingFaces());
}

void ProgressWindow::detectingFacesGaugePlusX(int x) {
	faces_found += x;
	detectingFacesTxt->SetLabelText(detectingFaces());
	detectingFacesGauge->SetValue(++images_analyzed);
}

void ProgressWindow::finishedDetectingFaces() {
	detectingFacesTxt->SetLabelText(detectingFacesDone());
	NNTxt->SetLabelText("Neural network is embedding faces, this could take a while..");
	NNGauge->Pulse();
}

void ProgressWindow::NNDone() {
	NNTxt->SetLabelText("Neural network finished embedding faces.");
	NNGauge->SetValue(10);
	NNGauge->Refresh();
}

void ProgressWindow::setComparingFacesRange(int r) {
	total_comparisons = Utils::sumUpToIncluding(r);
	comparingFacesTxt->SetLabel(comparingFaces());
	comparingFacesGauge->SetRange(total_comparisons);
}

void ProgressWindow::comparingFacesGougeSetX(int x) {
	faces_compared = x;
	comparingFacesTxt->SetLabelText(comparingFaces());
	comparingFacesGauge->SetValue(faces_compared);
}

void ProgressWindow::finishedComparingFaces() {
	comparingFacesTxt->SetLabelText(comparingFacesDone());
}
