#include "MainFrame.h"

#pragma region "GUI Setup"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxBoxSizer* clientAreaSizer = new wxBoxSizer(wxVERTICAL);

	createTitle(clientAreaSizer);
	createInfo(clientAreaSizer);
	createSelectFolderAndRunOn(clientAreaSizer);
	createRunButton(clientAreaSizer);

	SetSizerAndFit(clientAreaSizer);
	SetMinSize(wxSize(400, 500));
	Layout();
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

void MainFrame::createSelectFolderAndRunOn(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectFolderAndRunOnSizer = new wxBoxSizer(wxHORIZONTAL);
	
	createSelectedFolderLocationTextField(selectFolderAndRunOnSizer);
	createSelectFolder(selectFolderAndRunOnSizer);
	createRunOn(selectFolderAndRunOnSizer);

	parentSizer->Add(selectFolderAndRunOnSizer, 0, wxEXPAND | wxALIGN_CENTER, 3);
}

void MainFrame::createSelectedFolderLocationTextField(wxBoxSizer* parentSizer) {
	wxBoxSizer* selectedFolderLoactionSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* selectedFolderLocation = new wxStaticText(this, FOLDER_LOCATION, "", wxDefaultPosition, wxSize(150, -1), wxALIGN_CENTER);
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

#pragma endregion "GUI Setup"

#pragma region "Events"
void MainFrame::onDirSelect(wxFileDirPickerEvent& event) {
	wxButton* runButton = static_cast<wxButton*>(FindWindowById(MainFrameIDs::RUN_BUTTON));
	runButton->Enable();
	
	wxStaticText* folderLocation = static_cast<wxStaticText*>(FindWindowById(MainFrameIDs::FOLDER_LOCATION));
	folderLocation->SetLabelText(event.GetPath());
}
void MainFrame::onRunButtonClick(wxCommandEvent& event) {
	wxStaticText* folderLocation = static_cast<wxStaticText*>(FindWindowById(MainFrameIDs::FOLDER_LOCATION));
	
	ConsoleOutputWindow* console = new ConsoleOutputWindow("Console");
	console->SetClientSize(400, 300);
	console->Center();
	console->Show(true);

	runAlgorithm(folderLocation->GetLabelText().ToStdString());
}
#pragma endregion "Events"

