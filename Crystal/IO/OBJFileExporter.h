#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
	}
	namespace IO {

class OBJFileExporter
{
public:
	bool exportOBJ(const std::experimental::filesystem::path& filePath, Scene::PolygonMeshScene& objects);

	bool exportMTL(const std::experimental::filesystem::path& filePath, Scene::PolygonMeshScene& objects);
};

	}
}