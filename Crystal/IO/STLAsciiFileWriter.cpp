#include "STLASCIIFileWriter.h"
#include <fstream>

using namespace Crystal::Shape;
using namespace Crystal::IO;

STLASCIIFileWriter::STLASCIIFileWriter(const TriangleMesh& mesh) :
	mesh(mesh)
{
}

bool STLASCIIFileWriter::write(const std::experimental::filesystem::path& filePath)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream);
}

bool STLASCIIFileWriter::write(std::ostream& stream)
{
	stream << "solid" << " " << title.c_str() << std::endl;

	const auto& faces = mesh.getFaces();
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