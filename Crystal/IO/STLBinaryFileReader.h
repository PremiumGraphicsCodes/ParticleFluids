#ifndef __CRYSTAL_IO_STL_BINARY_FILE_READER_H__
#define __CRYSTAL_IO_STL_BINARY_FILE_READER_H__

#include "../Shape/TriangleMesh.h"

#include <fstream>

#include <vector>
#include <filesystem>

namespace Crystal {
	namespace IO {

class STLBinaryFileReader
{
public:
	STLBinaryFileReader()
	{}

	bool read(const std::experimental::filesystem::path& filePath);

	bool read(std::istream& stream);

private:
	std::vector<Shape::TriangleFace> faces;
	std::string title;
};

	}
}

#endif