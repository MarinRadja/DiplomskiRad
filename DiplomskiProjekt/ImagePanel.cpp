#include "ImagePanel.h"



BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
    EVT_PAINT(ImagePanel::paintEvent)
    EVT_SIZE(ImagePanel::OnSize)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent) :
    wxPanel(parent) {
    ::wxInitAllImageHandlers();
}

void ImagePanel::displayFace(std::string imageLocation) {
    image = Utils::simple_wx_from_mat(imageLocation); 
    setWidthAndHeight();
}

void ImagePanel::displayFace(cv::Mat cvImage) {
    image = Utils::simple_wx_from_mat(cvImage); 
    setWidthAndHeight();
}

void ImagePanel::paintEvent(wxPaintEvent& evt) {
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}
void ImagePanel::paintNow() {
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC& dc) {
    int posX, posY;
    int newW, newH;
    
    dc.GetSize(&newW, &newH);
    posX = 1. * newW / 2;
    posY = 1. * newH / 2;

    keepAspectRatio(&newW, &newH);
    posX -= 1. * newW / 2;
    posY -= 1. * newH / 2;

    if (newW != w || newH != h) {
        wxImage wxi = image.Scale(newW, newH, wxIMAGE_QUALITY_HIGH);
        resized = wxBitmap(wxi);
        dc.DrawBitmap(resized, posX, posY, false);
    } else {
        dc.DrawBitmap(resized, posX, posY, false);
    }
}

void ImagePanel::keepAspectRatio(int* frameW, int* frameH) {
    float w_ratio = 1. * w / *frameW;
    float h_ratio = 1. * h / *frameH;

    if (w_ratio > h_ratio) {
        *frameW = w / w_ratio;
        *frameH = h / w_ratio;
    } else {
        *frameW = w / h_ratio;
        *frameH = h / h_ratio;
    }
}

void ImagePanel::setWidthAndHeight() {
    w = image.GetSize().x;
    h = image.GetSize().y;
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void ImagePanel::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}