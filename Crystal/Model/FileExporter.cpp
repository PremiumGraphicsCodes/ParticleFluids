#include "FileExporter.h"

#include <filesystem>

#include "OBJFileExporter.h"

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
	{
		OBJFileExporter exporter;
		return exporter.exportOBJ(filePath, objects);
	}
	case FileFormat::MTL :
	{
		OBJFileExporter exporter;
		return exporter.exportMTL(filePath, appearances);
	}
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

