#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBScene;
		class VDBPointsScene;
		class VDBPolygonMeshScene;

class VDBFileExporter
{
public:
	explicit VDBFileExporter(const VDBScene* scene) :
		scene(scene)
	{}

	bool writePLY(const std::string& filePath);

	bool writePCD(const std::string& filePath);

	bool writeSTL(const std::string& filePath);

	bool writeOBJ(const std::string& filePath);

private:
	const VDBScene* scene;
};
	}
}