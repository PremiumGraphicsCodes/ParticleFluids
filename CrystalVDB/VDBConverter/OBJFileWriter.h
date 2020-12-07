#pragma once

#include "PolygonMesh.h"
#include <string>

namespace Crystal {
	namespace VDB {

class OBJFileWriter
{
public:
	bool write(const std::string& filePath, const VDBPolygonMesh& mesh);

	bool write(std::ostream& stream, const VDBPolygonMesh& obj);
};
	}
}
