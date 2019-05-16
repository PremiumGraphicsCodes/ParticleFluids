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
	stream
		<< "# .PCD v.7 - Point Cloud Data file format" << std::endl
		<< "VERSION "
		<< ".7" << std::endl
		<< "FIELDS "
		<< "x y z rgb" << std::endl
		<< "SIZE "
		<< "4 4 4 4" << std::endl
		<< "TYPE "
		<< "F F F F" << std::endl
		<< "COUNT "
		<< "1 1 1 1" << std::endl
		<< "WIDTH "
		<< header.width << std::endl
		<< "HEIGHT "
		<< "1" << std::endl
		<< "VIEWPOINT "
		<< "0 0 0 1 0 0 0" << std::endl
		<< "POINTS "
		<< header.points << std::endl
		<< "DATA "
		<< "ascii" << std::endl;

	return true;
}

bool PCDFileWriter::write(std::ostream& stream, const PCDFile::Data& data)
{
	const auto& positions = data.positions;
	for (const auto& p : positions) {
		const float color = 0.0f;
		stream << p.x << " " <<  p.y << " " <<  p.z << " " << color << std::endl;
	}
	return true;
}

