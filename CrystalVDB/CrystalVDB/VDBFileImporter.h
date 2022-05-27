#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBParticleSystemScene;
		class VDBPolygonMeshScene;

class VDBFileImporter
{
public:
	VDBParticleSystemScene* readPLY(const std::string& filePath);

	VDBParticleSystemScene* readPCD(const std::string& filePath);

	VDBPolygonMeshScene* readOBJ(const std::string& filePath);

	VDBPolygonMeshScene* readSTL(const std::string& filePath);
};
	}
}