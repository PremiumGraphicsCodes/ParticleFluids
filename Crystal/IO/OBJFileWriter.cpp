#include "OBJFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool OBJFileWriter::write(const std::experimental::filesystem::path& filename, const OBJFile& obj)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, obj);
}

bool OBJFileWriter::write(std::ostream& stream, const OBJFile& obj)
{
	// vertices
	const auto& vertices = obj.positions;
	for (const auto& v : vertices) {
		stream << "v " << v.x << " " << v.y << " " << v.z << std::endl;
	}

	// tex coords
	const auto& texCoords = obj.texCoords;
	for (const auto& vt : texCoords) {
		stream << "vt " << vt.x << " " << vt.y << std::endl;
	}

	// normals
	return false;
}
