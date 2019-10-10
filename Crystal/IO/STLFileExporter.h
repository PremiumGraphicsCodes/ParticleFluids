#pragma once

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;

class STLFileExporter
{
public:
	bool exportSTLAscii(const std::filesystem::path& filePath, PolygonMeshScene& objects);

	bool exportSTLBinary(const std::filesystem::path& filePath, PolygonMeshScene& objects);
};

	}
}