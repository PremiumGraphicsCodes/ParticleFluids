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
	const auto& normals = obj.normals;
	for (const auto& vn : normals) {
		stream << "vn " << vn.x << " " << vn.y << " " << vn.z << std::endl;
	}

	const auto& groups = obj.groups;
	for (const auto& g : groups) {
		// faces
		const auto& faces = g.faces;
		for (const auto& f : faces) {
			stream << "f";
			for (int i = 0; i < f.positionIndices.size(); ++i) {
				stream << " " << f.positionIndices[i] << "/" << f.texCoordIndices[i] << "/" << f.normalIndices[i];
			}
			stream << std::endl;
		}
	}
	return false;
}
