#ifndef __CRYSTAL_IO_STL_BINARY_FILE_READER_H__
#define __CRYSTAL_IO_STL_BINARY_FILE_READER_H__

#include "STLFile.h"

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

	bool read(const std::filesystem::path& filePath);

	bool read(std::istream& stream);

	STLFile getSTL() const { return stl; }

private:
	STLFile stl;
};

	}
}

#endif