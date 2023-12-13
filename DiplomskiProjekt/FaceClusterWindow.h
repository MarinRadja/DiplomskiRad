#pragma once
#define _WINSOCKAPI_
#include <wx/wx.h>
#include <wx/statline.h>

#include "ImagePanel.h"
#include "FaceGraph.h"
#include "IDs.h"


class FaceClusterWindow : public wxFrame {
public:
	FaceClusterWindow(const wxString& title, FaceGraph* _face_graph);
protected:
private:
	ImagePanel* bigImage;
	ImagePanel* faceImage;
	FaceGraph* face_graph;

	size_t i_face = 0;
	size_t i_cluster = 0;

	void createImagePanel(wxBoxSizer* parentSizer);
	void createSidebar(wxBoxSizer* parentSizer);
	void createFaceClusterTitle(wxBoxSizer* parentSizer);
	void createMiniFace(wxBoxSizer* parentSizer);
	void createControlForCurrentCluster(wxBoxSizer* parentSizer);
	void createHorizontalLine(wxBoxSizer* parentSizer);
	void createOpenImgLocationButton(wxBoxSizer* parentSizer);
	void createPrevFaceClusterButton(wxBoxSizer* parentSizer);
	void createNextFaceClusterButton(wxBoxSizer* parentSizer);
	void displayCurrentImage();


	void showPrevFaceImage(wxCommandEvent& event);
	void showNextFaceImage(wxCommandEvent& event);
	void showPrevCluster(wxCommandEvent& event);
	void showNextCluster(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

