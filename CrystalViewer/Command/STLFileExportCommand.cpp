#include "STLFileExportCommand.h"

#include "../../Crystal/IO/STLASCIIFileWriter.h"
#include "../../Crystal/IO/STLBinaryFileWriter.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "Public/FileExportLabels.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileExportCommand::Args::Args() :
	id(::IdLabel, -1),
	isBinary(::IsBinaryLabel, false),
	filePath(::FilePathLabel, "")
{
	add(&id);
	add(&isBinary);
	add(&filePath);
}

STLFileExportCommand::Results::Results() :
	isOk(::IsOkLabel, false)
{
	add(&isOk);
}

std::string STLFileExportCommand::getName()
{
	return ::STLFileExportCommandLabel;
}

void STLFileExportCommand::execute(World* scene)
{
	auto mesh = scene->getObjects()->findSceneById<PolygonMeshScene*>(args.id.getValue());
	if (args.isBinary.getValue()) {
		exportBinary(*mesh);
	}
	else {
		exportAscii(*mesh);
	}
}

void STLFileExportCommand::exportAscii(PolygonMeshScene& polygonMesh)
{
	std::vector<Scene::TriangleFace> fs;
	const auto& positions = polygonMesh.getShape()->getPositions();
	const auto& faces = polygonMesh.getShape()->getFaces();
	for (const auto& f : faces) {
		/*
		if (f->isDegenerated(1.0e-12f)) {
			continue;
		}
		*/
		const auto& vIds = f.getVertexIds();
		const auto v1 = positions[ vIds[0] ];
		const auto v2 = positions[ vIds[1] ];
		const auto v3 = positions[ vIds[2] ];
		TriangleFace ff({ v1,v2,v3 });
		//const auto area = ff.toTriangle().getArea();
		fs.push_back(ff);
	}
	STLASCIIFileWriter writer;
	STLFile stl;
	stl.faces = fs;
	writer.write(args.filePath.getValue(), stl);
}

void STLFileExportCommand::exportBinary(PolygonMeshScene& polygonMesh)
{
	std::vector<TriangleFace> fs;
	const auto& positions = polygonMesh.getShape()->getPositions();
	const auto& faces = polygonMesh.getShape()->getFaces();
	for (const auto& f : faces) {
		/*
		if (f->isDegenerated(1.0e-12f)) {
			continue;
		}
		*/
		const auto& vIds = f.getVertexIds();
		const auto v1 = positions[vIds[0]];
		const auto v2 = positions[vIds[1]];
		const auto v3 = positions[vIds[2]];
		TriangleFace ff({ v1,v2,v3 });
		//const auto area = ff.toTriangle().getArea();
		fs.push_back(ff);
	}
	STLFile stl;
	stl.faces = fs;
	stl.faceCount = fs.size();
	STLBinaryFileWriter writer;
	writer.write(args.filePath.getValue(), stl);
}
