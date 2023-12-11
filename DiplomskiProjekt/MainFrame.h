#pragma once
#include <wx/wx.h>
#include <wx/filepicker.h>

#include "IDs.h"
#include "ConsoleOutputWindow.h"
#include "RunAlgorithm.h"
#include "FaceClusterWindow.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
protected:
private:
	RunAlgorithm runAlg;

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