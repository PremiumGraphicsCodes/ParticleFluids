#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;

class STLFileExporter
{
public:
	bool exportSTLAscii(const std::experimental::filesystem::path& filePath, PolygonMeshScene& objects);

	bool exportSTLBinary(const std::experimental::filesystem::path& filePath, PolygonMeshScene& objects);
};

	}
}