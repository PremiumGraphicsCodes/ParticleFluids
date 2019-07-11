#include "STLFileExporter.h"

#include "../IO/STLASCIIFileWriter.h"
#include "../IO/STLBinaryFileWriter.h"

#include "PolygonMeshScene.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;

bool STLFileExporter::exportSTLAscii(const std::experimental::filesystem::path& filePath, PolygonMeshScene& polygonMesh)
{
	std::vector<Shape::TriangleFace> fs;
	const auto& vertices = polygonMesh.getShape()->getVertices();
	const auto& faces = polygonMesh.getShape()->getFaces();
	for (const auto& f : faces) {
		/*
		if (f->isDegenerated(1.0e-12f)) {
			continue;
		}
		*/
		const auto v1 = vertices[ f.v1 ]->getPosition();
		const auto v2 = vertices[ f.v2 ]->getPosition();
		const auto v3 = vertices[ f.v3 ]->getPosition();
		Shape::TriangleFace ff({ v1,v2,v3 });
		//const auto area = ff.toTriangle().getArea();
		fs.push_back(ff);
	}
	Shape::TriangleMesh mesh(fs);
	STLASCIIFileWriter writer;
	STLFile stl;
	stl.faces = mesh.getFaces();
	return writer.write(filePath, stl);
}

bool STLFileExporter::exportSTLBinary(const std::experimental::filesystem::path& filePath, PolygonMeshScene& polygonMesh)
{
	std::vector<Shape::TriangleFace> fs;
	const auto& vertices = polygonMesh.getShape()->getVertices();
	const auto& faces = polygonMesh.getShape()->getFaces();
	for (const auto& f : faces) {
		/*
		if (f->isDegenerated(1.0e-12f)) {
			continue;
		}
		*/
		const auto v1 = vertices[f.v1]->getPosition();
		const auto v2 = vertices[f.v2]->getPosition();
		const auto v3 = vertices[f.v3]->getPosition();
		Shape::TriangleFace ff({ v1,v2,v3 });
		//const auto area = ff.toTriangle().getArea();
		fs.push_back(ff);
	}
	STLFile stl;
	stl.faces = fs;
	stl.faceCount = fs.size();
	STLBinaryFileWriter writer;
	return writer.write(filePath, stl);
}
