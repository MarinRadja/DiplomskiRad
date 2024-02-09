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

	void detectingImagesPlusX(int x);
	void finishedDetectingImages();
	void detectingFacesPlusOne();
	void detectingFacesGaugePlusX(int x);
	void finishedDetectingFaces();
	void NNDone();
	void setComparingFacesRange(int r);
	void comparingFacesGougeSetX(int x); 
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
	wxStaticText* NNTxt;
	wxStaticText* comparingFacesTxt;

	wxGauge* detectingImagesGauge;
	wxGauge* detectingFacesGauge;
	wxGauge* NNGauge;
	wxGauge* comparingFacesGauge;

	void createImagesFoundProgress(wxBoxSizer* parentSizer);
	void createFindingFacesOnImagesProgress(wxBoxSizer* parentSizer);
	void createNNProgress(wxBoxSizer* parentSizer);
	void createClusteringFacesProgress(wxBoxSizer* parentSizer);

	void createImagesFoundText(wxBoxSizer* parentSizer);
	void createImagesFoundGauge(wxBoxSizer* parentSizer);
	void createDetectingFacesText(wxBoxSizer* parentSizer);
	void createDetectingFacesGauge(wxBoxSizer* parentSizer);
	void createNNText(wxBoxSizer* parentSizer);
	void createNNGauge(wxBoxSizer* parentSizer);
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
