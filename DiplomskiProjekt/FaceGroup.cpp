#include "FaceGroup.h"

void FaceGroup::addFace(Face face) {
	faces.push_back(face);
}

void FaceGroup::removeFace(int i) {
	if (i >= faces.size()) return;
	faces.erase(faces.begin() + i);
}
