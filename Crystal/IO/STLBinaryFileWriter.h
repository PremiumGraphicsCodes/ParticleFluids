#pragma once

#include <filesystem>
#include "../Shape/TriangleMesh.h"

namespace Crystal {
	namespace IO {

class STLBinaryFileWriter
{
public:
	explicit STLBinaryFileWriter(const std::vector<Shape::TriangleFace>& faces);

	bool write(const std::experimental::filesystem::path& filePath);

	bool write(std::ostream& stream);

private:
	std::string title;
	std::vector<Shape::TriangleFace> faces;
};
	}
}