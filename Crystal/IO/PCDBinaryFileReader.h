#pragma once

#include <string>
#include <filesystem>

#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PCDBinaryFileReader
{
public:
	bool read(std::istream& stream);

	bool read(const std::filesystem::path& filename);

	PCDFile getPCD() const { return pcd; }

private:
	PCDFile::Header readHeader(std::istream& stream);

	PCDFile::Data readData(std::istream& stream, const int howMany);

private:
	bool isOk;
	PCDFile pcd;
};

	}
}