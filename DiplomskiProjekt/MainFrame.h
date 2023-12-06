#pragma once
#include <wx/wx.h>
#include <wx/filepicker.h>

#include "IDs.h"
#include "Main.cpp"
#include "ConsoleOutputWindow.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
protected:
private:
	void createTitle(wxBoxSizer* parentSizer);
	void createInfo(wxBoxSizer* parentSizer);
	void createSelectedFolderLocationTextField(wxBoxSizer* parentSizer);
	void createSelectFolderAndRunOn(wxBoxSizer* parentSizer);
	void createSelectFolder(wxBoxSizer* parentSizer);
	void createRunOn(wxBoxSizer* parentSizer);
	void createRunButton(wxBoxSizer* parentSizer);

	void onDirSelect(wxFileDirPickerEvent& event);
	void onRunButtonClick(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_DIRPICKER_CHANGED(wxID_ANY, MainFrame::onDirSelect)
EVT_BUTTON(MainFrameIDs::RUN_BUTTON, MainFrame::onRunButtonClick)
wxEND_EVENT_TABLE()