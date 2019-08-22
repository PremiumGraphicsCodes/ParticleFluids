#pragma once

#include "Face.h"

namespace Crystal {
	namespace Shape {

class FaceGroup
{
public:
	FaceGroup(int id, int materialId) :
		id(id),
		materialId(materialId)
	{}

	void addFace(Face f) { this->faces.push_back(f); }

	std::vector<Face> getFaces() const { return faces; }

	int getId() const { return id; }

	int getMaterialId() const { return materialId; }

private:
	int id;
	int materialId;
	std::vector<Face> faces;
};

	}
}