#include "ConsoleOutputWindow.h"


#pragma region "GUI Setup"

ConsoleOutputWindow::ConsoleOutputWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxBoxSizer* consoleSizer = new wxBoxSizer(wxVERTICAL);

	wxTextCtrl* console = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1), wxALIGN_RIGHT);
	consoleSizer->Add(console, 1, wxEXPAND | wxALIGN_CENTER, 3);


	wxStreamToTextRedirector redirect(console);

	SetSizerAndFit(consoleSizer);
	SetMinSize(wxSize(400, 500));
	Layout();
}


#pragma endregion "GUI Setup"