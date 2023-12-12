#pragma once
#define _WINSOCKAPI_
#include <chrono>
#include <thread>

#include <wx/wx.h>
#include <wx/event.h>

#include "MainFrame.h"
#include "ProgressWindow.h"
#include "FaceClusterWindow.h"
#include "Utils.h"
#include "IDs.h"


class MyApp : public wxApp {
private:
	MainFrame* main_frame;
	ProgressWindow* progress_window;
	FaceClusterWindow* face_cluster_window; 
	
	void startWorking(string folderLocation);
public:
	bool OnInit();

	void createProgressWindow(wxCommandEvent& evt);
	void createFaceClusterWindow(wxCommandEvent& evt);
	void updateProgressWindow_detectedImage(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingImages(wxCommandEvent& evt);
	void updateProgressWindow_detectedFace(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingFacesOnImage(wxCommandEvent& evt);
	void updateProgressWindow_doneDetectingFaces(wxCommandEvent& evt);
	void updateProgressWindow_comparedFace(wxCommandEvent& evt);
	void updateProgressWindow_doneComparingFaces(wxCommandEvent& evt);
};

DECLARE_APP(MyApp);
