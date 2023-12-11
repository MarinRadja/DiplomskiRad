#pragma once
#include <wx/wx.h>

#include "IDs.h"

class ProgressWindow : public wxFrame {
public:
	ProgressWindow(const wxString& title);

	void setImagesFound(int x);
	void setImagesAnalyzed(int x);
	void setFacesFound(int x);
	void setFacesAnalyzed(int x);

	void detectingImagesPlusOne();
	void finishedDetectingImages();
protected:
private:
	int images_found;
	int faces_found;
	int images_analyzed;
	int faces_analyzed;

	void createImagesFoundText(wxBoxSizer* parentSizer);
	void createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer);
	void createClusteringFacesProgress(wxBoxSizer* parentSizer);
	void createDetectingFacesText(wxBoxSizer* parentSizer);
	void createDetectingFacesGauge(wxBoxSizer* parentSizer);
	void createClusteringFacesText(wxBoxSizer* parentSizer);
	void createClusteringFacesGauge(wxBoxSizer* parentSizer);

	std::string detectingImages();
	std::string detectingImagesDone();
	std::string detectingFaces();
	std::string detectingFacesDone();
	std::string clusteringFaces();
	std::string clusteringFacesDone();
};
