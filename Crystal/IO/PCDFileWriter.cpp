#include "PCDFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PCDFileWriter::write(const std::experimental::filesystem::path& filename, const PCDFile& pcd)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, pcd);
}

bool PCDFileWriter::write(std::ostream& stream, const PCDFile& pcd)
{
	if (!write(stream, pcd.header)) {
		return false;
	}
	if (!write(stream, pcd.data)) {
		return false;
	}
	return true;
}

bool PCDFileWriter::write(std::ostream& stream, const PCDFile::Header& header)
{
	return false;
}

bool PCDFileWriter::write(std::ostream& stream, const PCDFile::Data& data)
{
	return true;
}

