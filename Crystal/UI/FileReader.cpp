#include "FileReader.h"

#include <filesystem>

#include "../IO/OBJFileReader.h"
#include "../IO/STLAsciiFileReader.h"
#include "../IO/PCDFileReader.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Model;
using namespace Crystal::UI;

bool FileReader::read(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
{
	const auto& ext = filePath.extension();
	if (ext == ".obj") {
		OBJFileReader reader;
		if (reader.read(filePath)) {
			;
			return true;
		}
	}
	else if (ext == ".stl") {
		STLASCIIFileReader reader;
		if (reader.read(filePath)) {
			PolygonMeshBuilder builder;
			const auto& stl = reader.getSTL();
			TriangleMesh mesh(stl.faces);
			builder.build(mesh);
			repository.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "STL");
		}
	}
	else if (ext == ".pcd") {
		PCDFileReader reader;
		if (reader.read(filePath)) {
			const auto& positions = reader.getPCD().data.positions;
			ParticleAttribute attr;
			attr.color = glm::vec4(0, 0, 0, 0);
			attr.size = 1.0;
			repository.getParticleSystems()->addObject(positions, attr, "PCD");
			return true;
		}
	}
	return false;
}
