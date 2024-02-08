#pragma once
#define _WINSOCKAPI_
#include <chrono>
#include <thread>

#include <wx/wx.h>
#include <wx/event.h>

#include "MainFrame.h"
#include "ProgressWindow.h"
#include "FaceClusterWindow.h"
#include "RunAlgorithm.h"
#include "FaceGraph.h"
#include "Utils.h"
#include "IDs.h"


class MyApp : public wxApp {
private:
	MainFrame* main_frame;
	ProgressWindow* progress_window;
	FaceClusterWindow* face_cluster_window;
	FaceGraph face_graph;
	RunAlgorithm* run_algorithm;
	
	void startWorking(string folderLocation);
public:
	bool OnInit();

	void createMainWindow();
	void createProgressWindow(wxCommandEvent& evt);
	void createFaceClusterWindow(bool canSearch);

	// events for updating progress window
	void updateProgressWindow_detectedImage(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingImages(wxCommandEvent& evt);
	void updateProgressWindow_detectedFace(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingFacesOnImage(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingFaces(wxCommandEvent& evt);
	void updateProgressWindow_NNDone(wxCommandEvent& evt);
	void updateProgressWindow_comparedFace(wxCommandEvent& evt);
	void updateProgressWindow_doneComparingFaces(wxCommandEvent& evt);
	void updateProgressWindow_doneClusteringFaces(wxCommandEvent& evt);
	void updateProgressWindow_doneSearchingPeople(wxCommandEvent& evt);

	void searchPeople(wxFileDirPickerEvent& evt);

	// events for loading exisitng graph
	void loadGraphFromDisk(wxCommandEvent& evt);
};

DECLARE_APP(MyApp);
