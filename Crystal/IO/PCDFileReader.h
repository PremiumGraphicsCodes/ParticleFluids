#pragma once

#include <string>
#include <filesystem>

#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PCDFileReader
{
public:
	bool read(std::istream& stream);

	bool read(const std::experimental::filesystem::path& filename);

	PCDFile getPCD() const { return pcd; }

private:
	PCDFile::Header readHeader(std::istream& stream);

	PCDFile::Data readData(std::istream& stream);

private:
	bool isOk;
	PCDFile pcd;
};
	}
}