#pragma once

#include <string>
#include <array>

#include "../Math/Triangle3d.h"
#include "../Shape/TriangleMesh.h"

namespace Crystal {
	namespace IO {

struct STLFile
{
	std::string header;
	size_t faceCount = 0;
	std::vector<Shape::TriangleFace> faces;
};

	}
}