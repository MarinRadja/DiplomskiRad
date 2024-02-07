#pragma once
#define _WINSOCKAPI_
#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/filepicker.h>

#include "ImagePanel.h"
#include "FaceGraph.h"
#include "IDs.h"

template<typename V>
V mod(const V& a, const V& b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}

class FaceClusterWindow : public wxFrame {
public:
	FaceClusterWindow(const wxString& title, FaceGraph* _face_graph);
protected:
private:
	ImagePanel* bigImage;
	ImagePanel* faceImage;

	wxTextCtrl* face_name_box;
	wxStaticText* face_index_box;

	wxTextCtrl* cluster_name_box;
	wxStaticText* cluster_index_box; 

	wxFilePickerCtrl* save_graph;

	wxCheckBox* face_selected_box;
	wxCheckBox* cluster_selected_box;

	FaceGraph* face_graph;

	int i_face = 0;
	int i_cluster = 0;

	int display_clusters = 3;

	void createImagePanel(wxBoxSizer* parentSizer);
	void createSidebar(wxBoxSizer* parentSizer);
	void createFaceSection(wxBoxSizer* parentSizer);
	void createClusterSection(wxBoxSizer* parentSizer);
	void createDropSection(wxBoxSizer* parentSizer);
	void createSaveGraphSection(wxBoxSizer* parentSizer);

	void createFaceTitle(wxBoxSizer* parentSizer);
	void createMiniFace(wxBoxSizer* parentSizer);
	void createSelectedFaceBox(wxBoxSizer* parentSizer);
	void createFaceControlButtons(wxBoxSizer* parentSizer);

	void createClusterTitle(wxBoxSizer* parentSizer);
	void createMiniClusters(wxBoxSizer* parentSizer);
	void createSelectedClusterBox(wxBoxSizer* parentSizer);
	void createClusterButtons(wxBoxSizer* parentSizer);

	void createOpenImgLocationButton(wxBoxSizer* parentSizer);

	void createSaveGraphSectionToggles(wxBoxSizer* parentSizer);
	void createSaveGraphButton(wxBoxSizer* parentSizer);
	void createSearchPeopleSection(wxBoxSizer* parentSizer);

	void createHorizontalLine(wxBoxSizer* parentSizer, int y_size);

	void displayCurrentImage();
	void removeIfMatches(bool isSelected);

	void showPrevFaceImage(wxCommandEvent& evt);
	void showNextFaceImage(wxCommandEvent& evt);
	void showPrevCluster(wxCommandEvent& evt);
	void showNextCluster(wxCommandEvent& evt);

	void selectedFace(wxCommandEvent& evt);
	void selectedCluster(wxCommandEvent& evt);

	void removeCurrentImage(wxCommandEvent& evt);
	void removeCurrentPerson(wxCommandEvent& evt);
	void removeSelected(wxCommandEvent& evt);
	void removeNonSelected(wxCommandEvent& evt);

	void saveGraphToDisk(wxFileDirPickerEvent& evt);
	void searchPeople(wxFileDirPickerEvent& evt);

	void saveCurrent();
};

