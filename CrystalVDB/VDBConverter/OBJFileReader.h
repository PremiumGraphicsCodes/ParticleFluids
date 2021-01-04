#pragma once

#include "VDBPolygonMesh.h"
#include <string>

namespace Crystal {
	namespace VDB {

class OBJFileReader
{
public:
	bool read(const std::string& filePath, VDBPolygonMesh& mesh);

	bool read(std::istream& stream, VDBPolygonMesh& obj);

private:
};
	}
}
