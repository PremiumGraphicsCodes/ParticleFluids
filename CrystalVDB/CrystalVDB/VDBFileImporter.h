#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBPointsScene;
		class VDBPolygonMeshScene;

class VDBFileImporter
{
public:
	VDBPointsScene* readPLY(const std::string& filePath);

	VDBPointsScene* readPCD(const std::string& filePath);

	VDBPolygonMeshScene* readOBJ(const std::string& filePath);

	VDBPolygonMeshScene* readSTL(const std::string& filePath);
};
	}
}