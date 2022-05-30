#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBPointsScene;
		class VDBPolygonMeshScene;

class VDBFileExporter
{
public:
	bool writePLY(VDBPointsScene* vdbPoints, const std::string& filePath);

	bool writePCD(VDBPointsScene* vdbPoints, const std::string& filePath);

	bool writeSTL(VDBPolygonMeshScene* mesh, const std::string& filePath);

	bool writeOBJ(VDBPolygonMeshScene* mesh, const std::string& filePath);
};
	}
}