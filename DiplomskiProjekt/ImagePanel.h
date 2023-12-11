#pragma once
#include <opencv2/opencv.hpp>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/window.h>

#include "Utils.h"

class ImagePanel : public wxPanel {
    wxImage image;
    wxBitmap resized;
    int w, h;

    void keepAspectRatio(int* frameW, int* frameH);
    void setWidthAndHeight();
public:
    ImagePanel(wxFrame* parent);

    void displayFace(std::string imageLocation);
    void displayFace(cv::Mat cvImage);
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};


