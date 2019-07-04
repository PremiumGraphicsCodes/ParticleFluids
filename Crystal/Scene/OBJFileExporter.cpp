#include "OBJFileExporter.h"

#include "../IO/OBJFileWriter.h"
#include "../IO/MTLFileWriter.h"

#include "PolygonMeshScene.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;

bool OBJFileExporter::exportOBJ(const std::experimental::filesystem::path& filePath, PolygonMeshScene& polygon)
{
	OBJFile obj;
	obj.groups.push_back(OBJGroup());
		const auto& vertices = polygon.getShape()->getVertices();
		const auto& faces = polygon.getShape()->getFaces();
		for (auto f : faces) {
			std::vector<int> indices;
			indices.push_back(f->getV1()->getAttr().id + 1);
			indices.push_back(f->getV2()->getAttr().id + 1);
			indices.push_back(f->getV3()->getAttr().id + 1);
			OBJFace face;
			face.positionIndices = indices;
			face.normalIndices = indices;
			face.texCoordIndices = indices;
			obj.groups[0].faces.push_back(face);
		}
		for (auto v : vertices) {
			obj.positions.push_back(v->getPosition());
			obj.normals.push_back(v->getNormal());
			obj.texCoords.push_back(v->getTexCoord());
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
