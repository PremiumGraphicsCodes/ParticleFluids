#include "FileWriter.h"

#include <filesystem>

#include "../IO/STLASCIIFileWriter.h"
#include "../IO/STLBinaryFileWriter.h"
#include "../IO/PCDFileWriter.h"

using namespace Crystal::IO;
using namespace Crystal::Model;

bool FileWriter::write(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto format = getFileFormat(filePath);
	return write(filePath, objects, format);
}

bool FileWriter::write(const std::experimental::filesystem::path& filePath, ObjectRepository& objects, const FileFormat format)
{
	switch (format) {
	case FileFormat::OBJ :
		return writeOBJ(filePath, objects);
	case FileFormat::STL_ASCII :
		return writeSTLAscii(filePath, objects);
	case FileFormat::STL_BINARY :
		return writeSTLBinary(filePath, objects);
	case FileFormat::PCD :
		return writePCD(filePath, objects);
	default :
		assert(false);
	}
	return false;
}

bool FileWriter::writeOBJ(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	return false;
}

bool FileWriter::writeSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
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

bool FileWriter::writeSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
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
	STLBinaryFileWriter writer(fs);
	STLFile stl;
	stl.faces = mesh.getFaces();
	return writer.write(filePath);
}

bool FileWriter::writePCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& positions = objects.getParticleSystems()->getAllVertices();
	PCDFile pcd;
	pcd.header.points = positions.size();
	pcd.header.width = positions.size();
	pcd.data.positions = std::vector<Math::Vector3dd>(positions.begin(), positions.end());
	PCDFileWriter writer;
	return writer.write(filePath, pcd);
}

