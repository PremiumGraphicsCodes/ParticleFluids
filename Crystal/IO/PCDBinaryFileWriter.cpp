#include "PCDBinaryFileWriter.h"
#include <fstream>

using namespace Crystal::IO;


bool PCDBinaryFileWriter::write(const std::filesystem::path& filename, const PCDFile& pcd)
{
	std::fstream ifs(filename, std::ios::binary);
	return write(ifs, pcd);
}

bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile& pcd)
{
	if (!write(stream, pcd.header)) {
		return false;
	}
	if (!write(stream, pcd.data)) {
		return false;
	}
	return true;
}


bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile::Header& header)
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
		<< "binary" << std::endl;

	return true;
}

bool PCDBinaryFileWriter::write(std::ostream& stream, const PCDFile::Data& data)
{
	const auto& positions = data.positions;
	for (const auto& p : positions) {
		const float color = 0.0f;
		stream.write((char*)&p.x, sizeof(float));
		stream.write((char*)&p.y, sizeof(float));
		stream.write((char*)&p.z, sizeof(float));
		stream.write((char*)&color, sizeof(float));
	}
	return true;

}
