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
	face_counter++;
	image_location = _image_location;
	face_location = saveFaceToDisk(_face, _img_name);
}

Face::Face(string _image_location, string _face_location) {
	image_location = _image_location;
	face_location = _face_location;
}

string Face::getImageLocation() {
	return image_location;
}

string Face::getFaceLocation() {
	return face_location;
}

nlohmann::json Face::getJson() {
	nlohmann::json faceJson = {
		{"image_location", image_location},
		{"face_location", face_location}
	};
	return faceJson;
}

void Face::setImageLocation(string _image_location) {
	image_location = _image_location;
}
