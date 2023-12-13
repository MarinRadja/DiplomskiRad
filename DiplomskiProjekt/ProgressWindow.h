#pragma once
#define _WINSOCKAPI_

#include "IDs.h"
#include "Utils.h"

#include <wx/wx.h>
#include <wx/event.h>


class ProgressWindow : public wxFrame {
public:
	ProgressWindow(const wxString& title);

	void setImagesFound(int x);
	void setImagesAnalyzed(int x);
	void setFacesFound(int x);
	void setFacesAnalyzed(int x);

	void detectingImagesPlusOne();
	void finishedDetectingImages();
	void detectingFacesPlusOne();
	void detectingFacesGaugePlusOne();
	void finishedDetectingFaces();
	void setComparingFacesRange(int r);
	void comparingFacesGougePlusOne(); 
	void finishedComparingFaces();

protected:
private:
	int images_found;
	int faces_found;
	int images_analyzed;
	int faces_analyzed;
	int faces_compared;
	int total_comparisons;

	wxStaticText* imagesFoundTxt; 
	wxStaticText* detectingFacesTxt; 
	wxGauge* detectingFacesGauge; 
	wxStaticText* comparingFacesTxt; 
	wxGauge* comparingFacesGauge;

	void createImagesFoundText(wxBoxSizer* parentSizer);
	void createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer);
	void createClusteringFacesProgress(wxBoxSizer* parentSizer);
	void createDetectingFacesText(wxBoxSizer* parentSizer);
	void createDetectingFacesGauge(wxBoxSizer* parentSizer);
	void createComparingFacesText(wxBoxSizer* parentSizer);
	void createComparingFacesGauge(wxBoxSizer* parentSizer);
	void createClusteringFacesText(wxBoxSizer* parentSizer);

	std::string detectingImages();
	std::string detectingImagesDone();
	std::string detectingFaces();
	std::string detectingFacesDone();
	std::string comparingFaces();
	std::string comparingFacesDone(); 
	std::string clusteringFaces();
	std::string clusteringFacesDone();

};
