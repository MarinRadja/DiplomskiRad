#pragma once
#include <wx/defs.h>

enum MainFrameIDs {
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
    DETECTING_IMAGE_TXT = wxID_LAST + 1,
    DETECTING_FACE_TXT,
    DETECTING_FACE_GAUGE,
    CLUSTERING_FACE_TXT,
    CLUSTERING_FACE_GAUGE
};

enum ProgressWindowEventsIDs {
    DETECTED_IMAGE = wxID_LAST + 1,
    DONE_DETECTING_IMAGES, 
    DONE_CLUSTERING_FACES
};