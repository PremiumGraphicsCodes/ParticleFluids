#pragma once

#include <string>
#include <array>

#include "../Math/Triangle3d.h"

namespace Crystal {
	namespace IO {

struct STLFace
{
	STLFace()
	{};

	STLFace(const Math::Triangle3d& triangle, const Math::Vector3dd& normal) : 
		triangle(triangle),
		normal(normal)
	{}

	Math::Triangle3d triangle;
	Math::Vector3dd normal;
};

struct STLFile
{
	std::string header;
	size_t faceCount = 0;
	std::vector<STLFace> faces;
};

	}
}