#include "MainFrame.h"

#pragma region "GUI Setup"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

#pragma region "Bind Events"
	Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::onDirSelect, this, wxID_ANY);
	Bind(wxEVT_BUTTON, &MainFrame::onRunButtonClick, this, MainFrameIDs::RUN_BUTTON);
	Bind(wxEVT_FILEPICKER_CHANGED, &MainFrame::onGraphFileSelect, this, wxID_ANY);
	Bind(wxEVT_BUTTON, &MainFrame::onLoadButtonClick, this, MainFrameIDs::LOAD_BUTTON);
#pragma endregion

	runAlg = new RunAlgorithm();

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxVERTICAL);

	createTitle(clientAreaSizer);
	createInfo(clientAreaSizer);

	createRunAlgSection(clientAreaSizer);
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
	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Face Recognizer", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTRE_HORIZONTAL);

	wxFont font = title->GetFont();
	font.SetPointSize(28);
	font.MakeLarger();
	title->SetFont(font);

	titleSizer->Add(title, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(titleSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

// add description and how to use
void MainFrame::createInfo(wxBoxSizer* parentSizer) {
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* info = new wxStaticText(this, wxID_ANY, "This is an application for facial recognition and w/e.", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTER);

	infoSizer->Add(info, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(infoSizer, 5, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createRunAlgSection(wxBoxSizer* parentSizer) {
	createSelectFolderAndRunOn(parentSizer);
	createRunButton(parentSizer);
}

void MainFrame::createLoadGraphSection(wxBoxSizer* parentSizer) {
	createLoadGraphLocationAndPicker(parentSizer);
	createLoadGraphButton(parentSizer);
}

void MainFrame::createSelectFolderAndRunOn(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectFolderAndRunOnSizer = new wxBoxSizer(wxHORIZONTAL);
	
	createSelectedFolderLocationTextField(selectFolderAndRunOnSizer);
	createSelectFolder(selectFolderAndRunOnSizer);
	createRunOn(selectFolderAndRunOnSizer);

	parentSizer->Add(selectFolderAndRunOnSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createSelectedFolderLocationTextField(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectedFolderLoactionSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* selectedFolderLocation = new wxStaticText(this, MainFrameIDs::FOLDER_LOCATION, "", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTER);
	wxColour colour = selectedFolderLocation->GetBackgroundColour();
	colour.SetRGB(0x00e0e0e0);
	selectedFolderLocation->SetBackgroundColour(colour);

	selectedFolderLoactionSizer->Add(selectedFolderLocation, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectedFolderLoactionSizer, 5, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createSelectFolder(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectFolderSizer = new wxBoxSizer(wxHORIZONTAL);
	wxDirPickerCtrl* selectFolder = new wxDirPickerCtrl(this, MainFrameIDs::DIR_PICKER, "/", "Select folder with pictures (subfolders supported)", wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST);

	selectFolderSizer->Add(selectFolder, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectFolderSizer, 3, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createRunOn(wxBoxSizer* parentSizer) {
	wxBoxSizer* runOnSizer = new wxBoxSizer(wxHORIZONTAL);

	wxArrayString choices;
	choices.Add("CPU");
	choices.Add("CUDA");

	wxRadioBox* choice = new wxRadioBox(this, wxID_ANY, "Run on", wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
	choice->Select(0);

	runOnSizer->Add(choice, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(runOnSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createRunButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* runButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* choice = new wxButton(this, MainFrameIDs::RUN_BUTTON, "Start!", wxDefaultPosition, wxDefaultSize);
	choice->Disable();

	runButtonSizer->Add(choice, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(runButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createLoadGraphLocationAndPicker(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectGraphAndPickerSizer = new wxBoxSizer(wxHORIZONTAL);

	createSelectedGraphLocationTextField(selectGraphAndPickerSizer);
	createLoadGraphPicker(selectGraphAndPickerSizer);

	parentSizer->Add(selectGraphAndPickerSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createSelectedGraphLocationTextField(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectedGraphLocationSizer = new wxBoxSizer(wxHORIZONTAL);
	load_graph_label = new wxStaticText(this, MainFrameIDs::GRAPH_LOCATION, "", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTER);
	wxColour colour = load_graph_label->GetBackgroundColour();
	colour.SetRGB(0x00e0e0e0);
	load_graph_label->SetBackgroundColour(colour);

	selectedGraphLocationSizer->Add(load_graph_label, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectedGraphLocationSizer, 5, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createLoadGraphPicker(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectGraphSizer = new wxBoxSizer(wxHORIZONTAL);
	load_graph_picker = new wxFilePickerCtrl(this, MainFrameIDs::GRAPH_PICKER,
		"/", "Select graph", "*.json", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST);

	selectGraphSizer->Add(load_graph_picker, 1, wxALIGN_CENTER, 3);
	parentSizer->Add(selectGraphSizer, 3, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createLoadGraphButton(wxBoxSizer* parentSizer) {
	wxBoxSizer* loadButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	load_graph_button = new wxButton(this, MainFrameIDs::LOAD_BUTTON, "Load graph!", wxDefaultPosition, wxDefaultSize);
	load_graph_button->Disable();

	loadButtonSizer->Add(load_graph_button, 1, wxEXPAND | wxALIGN_CENTER, 3);
	parentSizer->Add(loadButtonSizer, 1, wxEXPAND | wxALIGN_CENTER, 3);
}

#pragma endregion "GUI Setup"

#pragma region "Events"

void MainFrame::onDirSelect(wxFileDirPickerEvent& evt) {
	wxButton* runButton = static_cast<wxButton*>(FindWindowById(MainFrameIDs::RUN_BUTTON));
	runButton->Enable();
	
	wxStaticText* folderLocation = static_cast<wxStaticText*>(FindWindowById(MainFrameIDs::FOLDER_LOCATION));
	folderLocation->SetLabelText(evt.GetPath());
}

void MainFrame::onRunButtonClick(wxCommandEvent& evt) {
	wxStaticText* folderLocation = static_cast<wxStaticText*>(FindWindowById(MainFrameIDs::FOLDER_LOCATION));
	
	/*ConsoleOutputWindow* console = new ConsoleOutputWindow("Console");
	console->SetClientSize(400, 300);
	console->Center();
	console->Show(true);*/


	this->Hide();

	wxCommandEvent* startWorking = new wxCommandEvent(myEVT_CREATE_PROGRESS_WINDOW, EventsIDs::CREATE_PROGRESS_WINDOW);
	startWorking->SetString(folderLocation->GetLabelText());
	wxTheApp->QueueEvent(startWorking);
}

void MainFrame::onGraphFileSelect(wxFileDirPickerEvent& evt) {
	load_graph_picker->Refresh();
	load_graph_button->Enable();
	load_graph_label->SetLabelText(evt.GetPath());
}

void MainFrame::onLoadButtonClick(wxCommandEvent& evt) {
	wxCommandEvent* startLoadingGraph = new wxCommandEvent(myEVT_LOAD_GRAPH_FROM_DISK);
	startLoadingGraph->SetString(load_graph_label->GetLabelText());
	wxTheApp->QueueEvent(startLoadingGraph);
}

#pragma endregion "Events"

