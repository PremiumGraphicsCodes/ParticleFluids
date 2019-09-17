#pragma once

#include <string>

#include <array>
#include "../Scene/TriangleFace.h"
#include "../Math/Triangle3d.h"

namespace Crystal {
	namespace IO {

struct STLFile
{
	std::string header;
	size_t faceCount = 0;
	std::vector<Scene::TriangleFace> faces;
};

	}
}