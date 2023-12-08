#include "Face.h"

Face::Face() {}

Face::Face(matrix<rgb_pixel> _face) {
	face = _face;
}

Face::Face(matrix<rgb_pixel> _face, string _image_location) {
	face = _face;
	image_location = _image_location;
}

string Face::getImageLocation() {
	return image_location;
}

matrix<float, 0, 1> Face::getFaceDescriptor() {
	return face_descriptor;
}

matrix<rgb_pixel> Face::getFacePtr() {
	return face;
}

void Face::setImageLocation(string _image_location) {
	image_location = _image_location;
}

void Face::setFaceDescriptor(matrix<float, 0, 1> _face_descriptor) {
	face_descriptor = _face_descriptor;
}

void Face::setFace(matrix<rgb_pixel> _face) {
	face = _face;
}

float Face::distanceFromFace(Face otherFace) {
	return length(face_descriptor - otherFace.getFaceDescriptor());
}
