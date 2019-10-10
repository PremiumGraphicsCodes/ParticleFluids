#pragma once

#include <string>
#include <filesystem>
#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PCDFileWriter
{
public:
	bool write(std::ostream& stream, const PCDFile& pcd);

	bool write(const std::filesystem::path& filename, const PCDFile& pcd);

private:
	bool write(std::ostream& stream, const PCDFile::Header& header);

	bool write(std::ostream& stream, const PCDFile::Data& data);

private:
};

	}
}