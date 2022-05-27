#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBParticleSystemScene;
		class VDBPolygonMeshScene;

class VDBFileExporter
{
public:
	bool writePLY(VDBParticleSystemScene* vdbPoints, const std::string& filePath);

	bool writePCD(VDBParticleSystemScene* vdbPoints, const std::string& filePath);

	bool writeSTL(VDBPolygonMeshScene* mesh, const std::string& filePath);

	bool writeOBJ(VDBPolygonMeshScene* mesh, const std::string& filePath);
};
	}
}