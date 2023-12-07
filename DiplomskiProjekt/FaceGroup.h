#pragma once
#include "face.h"

class FaceGroup {
private:
	std::vector<Face> faces;
public:
	void addFace(Face face);
	void removeFace(int i);
};

