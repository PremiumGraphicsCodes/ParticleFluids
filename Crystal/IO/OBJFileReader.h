#pragma once

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include "../Shape/PolygonMesh.h"
#include <filesystem>

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

class OBJFileReader
{
public:

	bool read(const std::experimental::filesystem::path& filePath);

	bool read(std::istream& stream);

	OBJFile getOBJ() const { return obj; }

private:

	Math::Vector3df readVertices(const std::string& str);

	Math::Vector3df readVector3d(const std::string& str);

	Math::Vector2df readVector2d(const std::string& str);

	OBJFile obj;
};

	}
}
