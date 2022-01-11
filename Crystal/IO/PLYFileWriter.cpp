#include "PLYFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PLYFileWriter::write(const std::filesystem::path& filename, const PLYFile& pcd)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, pcd);
}

bool PLYFileWriter::write(std::ostream& stream, const PLYFile& pcd)
{
	stream << "ply" << std::endl;
	stream << "format ascii 1.0" << std::endl;
	stream << "comment " << std::endl;
	stream << "comment " << std::endl;
	stream << "obj_info " << std::endl;
	stream << "element vertex " << pcd.vertices.size() << std::endl;
	stream << "property float x " << std::endl;
	stream << "property float y " << std::endl;
	stream << "property float z " << std::endl;
	//stream << "property uchar red " << std::endl;
	//stream << "property uchar green " << std::endl;
	//stream << "property uchar blue " << std::endl;
	stream << "end_header " << std::endl;

	const auto& positions = pcd.vertices;
	for (const auto& p : positions) {
		stream
			<< p.position.x << " "
			<< p.position.y << " "
			<< p.position.z << " " << std::endl;
	}
	return true;
}