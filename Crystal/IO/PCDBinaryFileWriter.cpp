#include "PCDBinaryFileWriter.h"

using namespace Crystal::IO;

bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile& pcd)
{
	return false;
}

bool PCDBinaryFileWriter::write(const std::filesystem::path& filename, const PCDFile& pcd)
{
	return false;
}

bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile::Header& header)
{
	return false;
}

bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile::Data& data)
{
	return false;
}
