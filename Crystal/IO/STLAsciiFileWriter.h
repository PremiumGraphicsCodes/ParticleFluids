#pragma once

#include "../Shape/TriangleMesh.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class STLASCIIFileWriter
{
public:
	explicit STLASCIIFileWriter(const Shape::TriangleMesh& mesh);

	bool write(const std::experimental::filesystem::path& filePath);

	bool write(std::ostream& stream);

private:
	std::string title;
	Shape::TriangleMesh mesh;
};
	}
}