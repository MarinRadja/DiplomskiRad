#include "MainFrame.h"

#pragma region "GUI Setup"

MainFrame::MainFrame(const wxString& title, RunAlgorithm* _run_algorithm) : wxFrame(nullptr, wxID_ANY, title) {
	runAlg = _run_algorithm;

#pragma region "Bind Events"
	Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::onDirSelect, this, wxID_ANY);
	Bind(wxEVT_BUTTON, &MainFrame::onRunButtonClick, this, MainFrameIDs::RUN_BUTTON);
	Bind(wxEVT_FILEPICKER_CHANGED, &MainFrame::onGraphFileSelect, this, wxID_ANY);
	Bind(wxEVT_BUTTON, &MainFrame::onLoadButtonClick, this, MainFrameIDs::LOAD_BUTTON);
#pragma endregion

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxVERTICAL);

	createTitle(clientAreaSizer);
	emptyTextLine(clientAreaSizer, 1);

	createInfo(clientAreaSizer);
	emptyTextLine(clientAreaSizer, 1);

	createRunAlgSection(clientAreaSizer);
	emptyTextLine(clientAreaSizer, 1);

	createLoadGraphSection(clientAreaSizer);

	SetSizerAndFit(clientAreaSizer);
	SetMinSize(wxSize(400, 500));
	Layout();

	::wxInitAllImageHandlers();
	// call function to load nn
}

RunAlgorithm* MainFrame::getAlgorithmPtr() {
	return runAlg;
}

void MainFrame::createTitle(wxBoxSizer* parentSizer) {
	wxBoxSizer* titleSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Raspoznavanje lica", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTRE);

	wxFont font = title->GetFont();
	font.SetPointSize(28);
	font.MakeLarger();
	title->SetFont(font);

	titleSizer->Add(title, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(titleSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

// add description and how to use
void MainFrame::createInfo(wxBoxSizer* parentSizer) {
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxTextCtrl* info = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(260, 200), wxTE_MULTILINE| wxTE_READONLY| wxTE_LEFT| wxTE_BESTWRAP | wxBORDER_NONE | wxTE_NO_VSCROLL);
	info->SetBackgroundColour(wxColor(*wxLIGHT_GREY));
	info->SetMargins(8);

	info->AppendText("Ovo je aplikacija za organiziranje slika osoba.\n");
	info->AppendText("Proèitajte readme.txt za detalnje upute!\n");
	info->AppendText("\n");
	info->AppendText("Prag sliènosti\n");
	info->AppendText("   - valjane vrijednosti: 1 - 1000\n");
	info->AppendText("   - zadano: 55, preporuèeno: 30 - 90\n");
	info->AppendText("\n");
	info->AppendText("Organiziraj slike:\n");
	info->AppendText("   - odaberite direktorij sa slikama\n");
	info->AppendText("   - pritisnite \"Pokreni analizu\"\n");
	info->AppendText("Uèitaj organizirane slike:\n");
	info->AppendText("   - odaberite spremljeni graf\n");
	info->AppendText("   - pritisnite \"Uèitaj graf\"");

	wxBoxSizer* emptyCol = new wxBoxSizer(wxVERTICAL);

	emptyCol->Add(new wxStaticText());
	infoSizer->Add(emptyCol, 1, wxEXPAND | wxALIGN_CENTER, 3);
	infoSizer->Add(info, 0, wxALIGN_CENTER, 3);
	infoSizer->Add(emptyCol, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(infoSizer, 3, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createRunAlgSection(wxBoxSizer* parentSizer) {
	createThreshold(parentSizer);
	createSelectFolderLblPkr(parentSizer);
	createRunButton(parentSizer);
}

void MainFrame::createLoadGraphSection(wxBoxSizer* parentSizer) {
	createLoadGraphLocationAndPicker(parentSizer);
	createLoadGraphButton(parentSizer);
}

void MainFrame::createThreshold(wxBoxSizer* parentSizer) {
	wxBoxSizer* createThresholdSIzer = new wxBoxSizer(wxHORIZONTAL);

	// label
	wxStaticText* thresholdText = new wxStaticText(this, wxID_ANY, "Prag sliènosti:\t", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

	// input
	similarity_threshold = new wxSpinCtrl(this, MainFrameIDs::SIMILARITY_THRESHOLD, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS|wxALIGN_RIGHT, 1, 1000, 55);

	createThresholdSIzer->Add(thresholdText, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 3);
	createThresholdSIzer->Add(similarity_threshold, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(createThresholdSIzer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createSelectFolderLblPkr(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectFolderSizer = new wxBoxSizer(wxHORIZONTAL);

	// label
	selected_folder_location = new wxTextCtrl(this, MainFrameIDs::GRAPH_LOCATION, "Odaberi direktorij sa slikama ->", wxDefaultPosition, wxSize(150, -1), wxTE_RIGHT | wxTE_READONLY | wxTE_NO_VSCROLL);
	selected_folder_location->SetBackgroundColour(wxColor(*wxLIGHT_GREY));

	// picker
	wxDirPickerCtrl* selectFolder = new wxDirPickerCtrl(this, MainFrameIDs::DIR_PICKER, "/", "Odaberite direktorij sa slikama", wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST);

	selectFolderSizer->Add(selected_folder_location, 3, wxALIGN_CENTER, 3);
	selectFolderSizer->Add(selectFolder, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectFolderSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createRunButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* runButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	run_alg_button = new wxButton(this, MainFrameIDs::RUN_BUTTON, "Pokreni analizu", wxDefaultPosition, wxDefaultSize);
	run_alg_button->Disable();

	runButtonSizer->Add(run_alg_button, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(runButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createLoadGraphLocationAndPicker(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectGraphSizer = new wxBoxSizer(wxHORIZONTAL);

	// label
	load_graph_label = new wxTextCtrl(this, MainFrameIDs::GRAPH_LOCATION, "Odaberi graf ->", wxDefaultPosition, wxSize(150, -1), wxTE_RIGHT | wxTE_READONLY | wxTE_NO_VSCROLL);
	load_graph_label->SetBackgroundColour(wxColor(*wxLIGHT_GREY));

	// picker
	load_graph_picker = new wxFilePickerCtrl(this, MainFrameIDs::GRAPH_PICKER,
		"/", "", "*.json", wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST);

	selectGraphSizer->Add(load_graph_label, 3, wxALIGN_CENTER, 3);
	selectGraphSizer->Add(load_graph_picker, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectGraphSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createLoadGraphButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* loadButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	load_graph_button = new wxButton(this, MainFrameIDs::LOAD_BUTTON, "Uèitaj graf", wxDefaultPosition, wxDefaultSize);
	load_graph_button->Disable();

	loadButtonSizer->Add(load_graph_button, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(loadButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::emptyTextLine(wxBoxSizer* parentSizer, int proportion) {
	wxBoxSizer* emptySizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* emptyText = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

	emptySizer->Add(emptyText, 1, wxALIGN_CENTER);
	parentSizer->Add(emptySizer, 0, wxALIGN_CENTER);
}

#pragma endregion "GUI Setup"

#pragma region "Events"

void MainFrame::onDirSelect(wxFileDirPickerEvent& evt) {
	run_alg_button->Enable();
	
	wxStaticText* folderLocation = static_cast<wxStaticText*>(FindWindowById(MainFrameIDs::FOLDER_LOCATION));
	selected_folder_location->Clear();
	selected_folder_location->AppendText(evt.GetPath());
}

void MainFrame::onRunButtonClick(wxCommandEvent& evt) {
	Utils::faceSimilarityThreshold = similarity_threshold->GetValue() / 100.;

	wxCommandEvent* startWorking = new wxCommandEvent(myEVT_CREATE_PROGRESS_WINDOW, EventsIDs::CREATE_PROGRESS_WINDOW);
	startWorking->SetString(selected_folder_location->GetLineText(0));
	wxTheApp->QueueEvent(startWorking);

	this->Hide();
}

void MainFrame::onGraphFileSelect(wxFileDirPickerEvent& evt) {
	load_graph_button->Enable();
	load_graph_label->Clear();
	load_graph_label->AppendText(evt.GetPath());
}

void MainFrame::onLoadButtonClick(wxCommandEvent& evt) {
	wxCommandEvent* startLoadingGraph = new wxCommandEvent(myEVT_LOAD_GRAPH_FROM_DISK);
	startLoadingGraph->SetString(load_graph_label->GetLineText(0));
	wxTheApp->QueueEvent(startLoadingGraph);
}

#pragma endregion "Events"

