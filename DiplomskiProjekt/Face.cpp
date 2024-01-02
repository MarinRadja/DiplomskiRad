#include "Face.h"

std::atomic<unsigned int> Face::face_counter = std::atomic<unsigned int>(0);

std::string Face::saveFaceToDisk(matrix<rgb_pixel>& face, string& _img_name) {
	Mat f;
	Utils::convertMatRGBPixelToCVMat(face, f);

	Utils::createDirectory("faces");
	std::string fLoc = "./faces/" + _img_name + "_" + std::to_string(face_counter) + ".jpeg";
	imwrite(fLoc, f);
	return fLoc;
}

Face::Face() {}

Face::Face(matrix<rgb_pixel>& _face, string& _image_location, string& _img_name) {
	face = _face;
	
	face_counter++;
	image_location = _image_location;
	face_location = saveFaceToDisk(face, _img_name);
}

string Face::getImageLocation() {
	return image_location;
}

matrix<float, 0, 1> Face::getFaceDescriptor() {
	return face_descriptor;
}

matrix<rgb_pixel> Face::getFace() {
	return face;
}

matrix<rgb_pixel>* Face::getFacePtr() {
	return &face;
}

Mat Face::getFaceOpenCV() {
	return dlib::toMat(face);
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
