#include "FileExporter.h"

#include <filesystem>

#include "../IO/OBJFileWriter.h"
#include "../IO/MTLFileWriter.h"
#include "../IO/STLASCIIFileWriter.h"
#include "../IO/STLBinaryFileWriter.h"
#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances)
{
	const auto format = getFileFormat(filePath);
	return exportFile(filePath, objects, appearances, format);
}

bool FileExporter::exportFile(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, AppearanceObjectRepository& appearances, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
		return exportOBJ(filePath, objects);
	case FileFormat::MTL :
		return exportMTL(filePath, appearances);
	case FileFormat::STL_ASCII :
		return exportSTLAscii(filePath, objects);
	case FileFormat::STL_BINARY :
		return exportSTLBinary(filePath, objects);
	case FileFormat::PCD :
		return exportPCD(filePath, objects);
	default :
		assert(false);
	}
	return false;
}

bool FileExporter::exportOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& polygons = objects.getPolygonMeshes()->getObjects();
	OBJFile obj;
	obj.groups.push_back(OBJGroup());
	for (auto p : polygons) {
		const auto& vertices = p->getShape()->getVertices();
		const auto& faces = p->getShape()->getFaces();
		for (auto f : faces) {
			std::vector<int> indices;
			indices.push_back(f->getV1()->getAttr().id +1);
			indices.push_back(f->getV2()->getAttr().id +1);
			indices.push_back(f->getV3()->getAttr().id +1);
			OBJFace face;
			face.positionIndices = indices;
			face.normalIndices = indices;
			face.texCoordIndices = indices;
			obj.groups[0].faces.push_back(face);
		}
		for (auto v : vertices) {
			obj.positions.push_back( v->getPosition() );
			obj.normals.push_back( v->getNormal() );
			obj.texCoords.push_back( v->getTexCoord() );
		}
	}
	OBJFileWriter writer;
	return writer.write(filePath, obj);
}

bool FileExporter::exportMTL(const std::experimental::filesystem::path& filePath, AppearanceObjectRepository& appearances)
{
	MTLFileWriter writer;
	MTLFile mtl;
	for (const auto mat : appearances.getMaterials()->getMaterials()) {
		MTL m;
		m.name = mat->getName();
	 	m.ambient = mat->getMaterial()->ambient;
		m.specular = mat->getMaterial()->specular;
		m.diffuse = mat->getMaterial()->diffuse;
		m.specularExponent = mat->getMaterial()->shininess;
		mtl.materials.push_back(m);
	}
	return writer.write(filePath, mtl);
}

bool FileExporter::exportSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& polygons = objects.getPolygonMeshes()->getObjects();
	std::vector<Shape::TriangleFace> fs;
	for (auto p : polygons) {
		const auto& faces = p->getShape()->getFaces();
		for (const auto& f : faces) {
			if (f->isDegenerated(1.0e-12)) {
				continue;
			}
			const auto v1 = f->getV1()->getPosition();
			const auto v2 = f->getV2()->getPosition();
			const auto v3 = f->getV3()->getPosition();
			Shape::TriangleFace ff({ v1,v2,v3 });
			//const auto area = ff.toTriangle().getArea();
			fs.push_back(ff);
		}
	}
	Shape::TriangleMesh mesh(fs);
	STLASCIIFileWriter writer;
	STLFile stl;
	stl.faces = mesh.getFaces();
	return writer.write(filePath, stl);
}

bool FileExporter::exportSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& polygons = objects.getPolygonMeshes()->getObjects();
	std::vector<Shape::TriangleFace> fs;
	for (auto p : polygons) {
		const auto& faces = p->getShape()->getFaces();
		for (const auto& f : faces) {
			if (f->isDegenerated(1.0e-12)) {
				continue;
			}
			const auto v1 = f->getV1()->getPosition();
			const auto v2 = f->getV2()->getPosition();
			const auto v3 = f->getV3()->getPosition();
			Shape::TriangleFace ff({ v1,v2,v3 });
			//const auto area = ff.toTriangle().getArea();
			fs.push_back(ff);
		}
	}
	STLFile stl;
	stl.faces = fs;
	stl.faceCount = fs.size();
	STLBinaryFileWriter writer;
	return writer.write(filePath, stl);
}

bool FileExporter::exportPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& positions = objects.getParticleSystems()->getAllVertices();
	PCDFile pcd;
	pcd.header.points = positions.size();
	pcd.header.width = positions.size();
	pcd.data.positions = std::vector<Math::Vector3dd>(positions.begin(), positions.end());
	PCDFileWriter writer;
	return writer.write(filePath, pcd);
}

