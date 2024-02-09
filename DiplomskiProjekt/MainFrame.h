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
#include <wx/spinctrl.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title, RunAlgorithm* _run_algorithm);
	~MainFrame() {};

	RunAlgorithm* getAlgorithmPtr();
protected:
private:
	RunAlgorithm* runAlg;

	wxSpinCtrl* similarity_threshold;
	wxTextCtrl* selected_folder_location;
	wxButton* run_alg_button;
	wxTextCtrl* load_graph_label;
	wxFilePickerCtrl* load_graph_picker;
	wxButton* load_graph_button;

	void createTitle(wxBoxSizer* parentSizer);
	void createInfo(wxBoxSizer* parentSizer);
	void createRunAlgSection(wxBoxSizer* parentSizer);
	void createLoadGraphSection(wxBoxSizer* parentSizer);

	// run alg section
	void createThreshold(wxBoxSizer* parentSizer);
	void createSelectedFolderLocationTextField(wxBoxSizer* parentSizer);
	void createSelectFolderLblPkr(wxBoxSizer* parentSizer);
	void createSelectFolder(wxBoxSizer* parentSizer);
	void createRunOn(wxBoxSizer* parentSizer);
	void createRunButton(wxBoxSizer* parentSizer);

	// load graph section
	void createLoadGraphLocationAndPicker(wxBoxSizer* parentSizer);
	void createSelectedGraphLocationTextField(wxBoxSizer* parentSizer);
	void createLoadGraphPicker(wxBoxSizer* parentSizer);
	void createLoadGraphButton(wxBoxSizer* parentSizer);

	void emptyTextLine(wxBoxSizer* parentSizer, int proportion);

	// events
	void onDirSelect(wxFileDirPickerEvent& evt);
	void onRunButtonClick(wxCommandEvent& evt);
	void onGraphFileSelect(wxFileDirPickerEvent& evt);
	void onLoadButtonClick(wxCommandEvent& evt);

	void startWorking(string folderLocation);

};