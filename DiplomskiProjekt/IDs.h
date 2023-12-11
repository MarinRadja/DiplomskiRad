#pragma once
#include <wx/wx.h>

enum MainFrameIDs{
    DIR_PICKER = wxID_LAST + 1,
    RUN_BUTTON,
    FOLDER_LOCATION
};

enum FaceClusterWindowIDs {
    PREV_IMG = wxID_LAST + 1,
    NEXT_IMG,
    OPEN_IMG_LOC,
    PREV_CLUSTER,
    NEXT_CLUSTER
};

enum ProgressWindowIDs {
    DETECTING_IMAGE_TXT = wxID_LAST +1,
    DETECTING_FACE_TXT,
    DETECTING_FACE_GAUGE,
    CLUSTERING_FACE_TXT,
    CLUSTERING_FACE_GAUGE
};