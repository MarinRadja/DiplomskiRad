#pragma once
#define _WINSOCKAPI_
#include "IDs.h"
#include "ConsoleOutputWindow.h"
#include "RunAlgorithm.h"
#include "FaceClusterWindow.h"
#include "ProgressWindow.h"

#include <thread>

#include <wx/wx.h>
#include <wx/filepicker.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);

	RunAlgorithm* getAlgorithmPtr();
protected:
private:
	RunAlgorithm* runAlg;

	void createTitle(wxBoxSizer* parentSizer);
	void createInfo(wxBoxSizer* parentSizer);
	void createSelectedFolderLocationTextField(wxBoxSizer* parentSizer);
	void createSelectFolderAndRunOn(wxBoxSizer* parentSizer);
	void createSelectFolder(wxBoxSizer* parentSizer);
	void createRunOn(wxBoxSizer* parentSizer);
	void createRunButton(wxBoxSizer* parentSizer);

	void onDirSelect(wxFileDirPickerEvent& event);
	void onRunButtonClick(wxCommandEvent& event);

	void startWorking(string folderLocation);

	wxDECLARE_EVENT_TABLE();
};