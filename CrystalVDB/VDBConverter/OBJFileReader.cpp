#include "OBJFileReader.h"

#include "../../Crystal/IO/OBJFileReader.h"

#include "Converter.h"

#include "PolygonMeshImpl.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shape;
using namespace Crystal::VDB;

bool OBJFileReader::read(const std::string& filePath, VDBPolygonMesh& mesh)
{
	std::ifstream stream;
	stream.open(filePath);

	if (!stream.is_open()) {
		return false;
	}

	return read(stream, mesh);
}

bool OBJFileReader::read(std::istream& stream, VDBPolygonMesh& mesh)
{
	Crystal::IO::OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	for (const auto& p : obj.positions) {
		mesh.getImpl()->points.push_back(Converter::toVDB(p));
	}

	for (const auto& group : obj.groups) {
		for (const auto& face : group.faces) {
			if (face.positionIndices.size() == 3) {
				openvdb::Vec3I i(face.positionIndices[0], face.positionIndices[1], face.positionIndices[2]);
				//mesh.getImpl()->triangles.push_back(i);
			}
			if (face.positionIndices.size() == 4) {
				openvdb::Vec4I i(face.positionIndices[0], face.positionIndices[1], face.positionIndices[2], face.positionIndices[3]);
				//mesh.getImpl()->quads.push_back(i);			
			}
		}
	}
	return true;
}