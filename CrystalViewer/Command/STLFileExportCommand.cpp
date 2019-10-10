#include "STLFileExportCommand.h"

#include "../../Crystal/IO/STLASCIIFileWriter.h"
#include "../../Crystal/IO/STLBinaryFileWriter.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string STLFileExportCommand::getName()
{
	return "STLFileExport";
}

void STLFileExportCommand::execute(World* scene)
{

}

void STLFileExportCommand::exportAscii(World* scene)
{
	//std::vector<Scene::TriangleFace> fs;
	//const auto& positions = polygonMesh.getShape()->getPositions();
	//const auto& faces = polygonMesh.getShape()->getFaces();
	//for (const auto& f : faces) {
	//	/*
	//	if (f->isDegenerated(1.0e-12f)) {
	//		continue;
	//	}
	//	*/
	//	const auto& vIds = f.getVertexIds();
	//	const auto v1 = positions[ vIds[0] ];
	//	const auto v2 = positions[ vIds[1] ];
	//	const auto v3 = positions[ vIds[2] ];
	//	Shape::TriangleFace ff({ v1,v2,v3 });
	//	//const auto area = ff.toTriangle().getArea();
	//	fs.push_back(ff);
	//}
	//Shape::TriangleMesh mesh(fs);
	//STLASCIIFileWriter writer;
	//STLFile stl;
	//stl.faces = mesh.getFaces();
	//return writer.write(filePath, stl);
}

void STLFileExportCommand::exportBinary(World* world)
{
	//std::vector<Shape::TriangleFace> fs;
	//const auto& positions = polygonMesh.getShape()->getPositions();
	//const auto& faces = polygonMesh.getShape()->getFaces();
	//for (const auto& f : faces) {
	//	/*
	//	if (f->isDegenerated(1.0e-12f)) {
	//		continue;
	//	}
	//	*/
	//	const auto& vIds = f.getVertexIds();
	//	const auto v1 = positions[vIds[0]];
	//	const auto v2 = positions[vIds[1]];
	//	const auto v3 = positions[vIds[2]];
	//	Shape::TriangleFace ff({ v1,v2,v3 });
	//	//const auto area = ff.toTriangle().getArea();
	//	fs.push_back(ff);
	//}
	//STLFile stl;
	//stl.faces = fs;
	//stl.faceCount = fs.size();
	//STLBinaryFileWriter writer;
	//return writer.write(filePath, stl);
}
