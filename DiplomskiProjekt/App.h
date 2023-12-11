#pragma once
#include "MainFrame.h"
#include "ProgressWindow.h"
#include "FaceClusterWindow.h"

#include <wx/wx.h>

class App : public wxApp
{
private:
	MainFrame* main_frame;
	ProgressWindow* progress_window;
	FaceClusterWindow* face_cluster_window;

public:
	bool OnInit();

	void createProgressWindow(wxCommandEvent& event);
	void createFaceClusterWindow(wxCommandEvent& event);
};

DECLARE_APP(App);
wxDECLARE_EVENT(EVT_SHOW_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_PROGRESS_WINDOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_SHOW_CLUSTERED_FACES_WINDOW, wxCommandEvent);
