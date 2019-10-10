#include "STLASCIIFileWriter.h"
#include <fstream>

using namespace Crystal::IO;

bool STLASCIIFileWriter::write(const std::filesystem::path& filePath, const STLFile& stl)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, stl);
}

bool STLASCIIFileWriter::write(std::ostream& stream, const STLFile& stl)
{
	stream << "solid" << " " << stl.header.c_str() << std::endl;

	const auto& faces = stl.faces;
	for (const auto& face : faces) {
		stream << "facet" << " ";
		const auto& normal = face.getNormal();
		stream << "normal" << " " << normal.x << " " << normal.y << " " << normal.z << std::endl;
		stream << "outer loop" << std::endl;
		const auto& positions = face.getVertices();
		for (const auto& pos : positions) {
			stream << "vertex" << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		}
		stream << "endloop" << std::endl;
		stream << "endfacet" << std::endl;
	}
	stream << "endsolid" << std::endl;

	return stream.good();
}