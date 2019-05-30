#pragma once

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct OBJFace
{
	std::vector<int> positionIndices;
	std::vector<int> normalIndices;
	std::vector<int> texCoordIndices;
};

struct OBJGroup
{
	std::vector< OBJFace > faces;
};

struct OBJFile
{
	std::string comment;

	std::vector< Math::Vector3df > positions;
	std::vector< Math::Vector3df > normals;
	std::vector< Math::Vector2df > texCoords;

	std::vector< OBJGroup > groups;
	std::vector< std::string > mtllibs;
	std::vector< std::pair< std::string, unsigned int> > useMtlNames;
};

	}
}