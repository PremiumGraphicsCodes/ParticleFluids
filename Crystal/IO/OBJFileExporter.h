#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
	}
	namespace IO {

class OBJFileExporter
{
public:
	bool exportOBJ(const std::filesystem::path& filePath, Scene::PolygonMeshScene& objects);

	bool exportMTL(const std::filesystem::path& filePath, Scene::PolygonMeshScene& objects);
};

	}
}