#pragma once

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct OBJFace
{
	std::vector<int> positionIndex;
	std::vector<int> normalIndex;
	std::vector<int> texCoordIndex;
};

struct OBJFile
{
	std::string comment;

	std::vector< Math::Vector3df > positions;
	std::vector< Math::Vector3df > normals;
	std::vector< Math::Vector2df > texCoords;

	std::vector< OBJFace > faces;

	std::vector< std::pair< std::string, unsigned int > > groups;
	std::vector< std::string > mtllibs;
	std::vector< std::pair< std::string, unsigned int> > useMtlNames;
};

	}
}