#ifndef __CRYSTAL_IO_STL_ASCII_FILE_READER_H__
#define __CRYSTAL_IO_STL_ASCII_FILE_READER_H__

#include "STLFile.h"

#include <fstream>

#include <vector>
#include <filesystem>

namespace Crystal {
	namespace IO {

class STLASCIIFileReader
{
public:
	STLASCIIFileReader()
	{}

	bool read(const std::experimental::filesystem::path& filePath);

	bool read(std::istream& stream);

	STLFile getSTL() const { return stl; }

private:
	STLFile stl;
};

	}
}

#endif