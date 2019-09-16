#include "OBJFileExporter.h"

#include "../IO/OBJFileWriter.h"
#include "../IO/MTLFileWriter.h"

#include "../Scene/PolygonMeshScene.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;

bool OBJFileExporter::exportOBJ(const std::experimental::filesystem::path& filePath, PolygonMeshScene& polygon)
{
	OBJFile obj;
	obj.groups.push_back(OBJGroup());
	const auto& vertices = polygon.getShape()->getVertices();
	const auto& faces = polygon.getShape()->getFaces();

	const auto& positions = polygon.getShape()->getPositions();
	for (const auto& v : positions) {
		obj.positions.push_back(v);
	}
	const auto& normals = polygon.getShape()->getNormals();
	for (const auto& n : normals) {
		obj.normals.push_back(n);
	}
	const auto& tcs = polygon.getShape()->getTexCoords();
	for (const auto& tc : tcs) {
		obj.texCoords.push_back(tc);
	}

	for (auto f : faces) {
		std::vector<int> indices;
		const auto& vIds = f.getVertexIds();
		indices.push_back(vIds[0] + 1);
		indices.push_back(vIds[1] + 1);
		indices.push_back(vIds[2] + 1);
		OBJFace face;
		face.positionIndices = indices;
		face.normalIndices = indices;
		face.texCoordIndices = indices;
		obj.groups[0].faces.push_back(face);
	}
	OBJFileWriter writer;
	return writer.write(filePath, obj);
}

bool OBJFileExporter::exportMTL(const std::experimental::filesystem::path& filePath, PolygonMeshScene& appearances)
{
	/*
	MTLFileWriter writer;
	MTLFile mtl;
	for (const auto mat : objects.getMaterials()->getMaterials()) {
		MTL m;
		m.name = mat->getName();
		m.ambient = mat->getMaterial()->ambient;
		m.specular = mat->getMaterial()->specular;
		m.diffuse = mat->getMaterial()->diffuse;
		m.specularExponent = mat->getMaterial()->shininess;
		mtl.materials.push_back(m);
	}
	return writer.write(filePath, mtl);
	*/
	return false;
}
