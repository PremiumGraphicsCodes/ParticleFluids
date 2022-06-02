#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBPointsScene;
		class VDBPolygonMeshScene;

class VDBPLYFileWriter
{
public:
	bool writePLY(VDBPointsScene* vdbPoints, const std::string& filePath);
};
	}
}