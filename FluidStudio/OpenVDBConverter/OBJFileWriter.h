#pragma once

#include "PolygonMesh.h"
#include <string>

namespace Crystal {
	namespace OpenVDB {

class OBJFileWriter
{
public:
	bool write(const std::string& filePath, const PolygonMesh& mesh);

	bool write(std::ostream& stream, const PolygonMesh& obj);
};
	}
}
