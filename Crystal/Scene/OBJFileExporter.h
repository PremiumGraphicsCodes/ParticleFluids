#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;

class OBJFileExporter
{
public:
	bool exportOBJ(const std::experimental::filesystem::path& filePath, PolygonMeshScene& objects);

	bool exportMTL(const std::experimental::filesystem::path& filePath, PolygonMeshScene& objects);
};

	}
}