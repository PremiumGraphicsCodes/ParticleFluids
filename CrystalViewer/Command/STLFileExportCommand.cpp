#include "STLFileExportCommand.h"

#include "../../Crystal/IO/STLASCIIFileWriter.h"
#include "../../Crystal/IO/STLBinaryFileWriter.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "Public/STLFileExportLabels.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileExportCommand::Args::Args() :
	ids(STLFileExportLabels::IdsLabel, {}),
	isBinary(STLFileExportLabels::IsBinaryLabel, false),
	filePath(STLFileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&isBinary);
	add(&filePath);
}

STLFileExportCommand::Results::Results()// :
//	isOk(FileExportLabels::IsOkLabel, false)
{
//	add(&isOk);
}

std::string STLFileExportCommand::getName()
{
	return STLFileExportLabels::CommandNameLabel;
}

bool STLFileExportCommand::execute(World* world)
{
	const auto ids = args.ids.getValue();

	STLFile stl;
	std::vector<Scene::TriangleFace> fs;
	for (const auto& id : ids) {
		auto polygonMesh = world->getObjects()->findSceneById<PolygonMeshScene*>(id);
		const auto& positions = polygonMesh->getShape()->getPositions();
		const auto& vertices = polygonMesh->getShape()->getVertices();
		const auto& faces = polygonMesh->getShape()->getFaces();
		for (const auto& f : faces) {
			/*
			if (f.isDegenerated(1.0e-12f)) {
				continue;
			}
			*/
			const auto& vIds = f.getVertexIds();
			const auto v1 = positions[ vertices[vIds[0]].positionId ];
			const auto v2 = positions[ vertices[vIds[1]].positionId ];
			const auto v3 = positions[ vertices[vIds[2]].positionId ];
			TriangleFace ff({ v1,v2,v3 });
			//const auto area = ff.toTriangle().getArea();
			fs.push_back(ff);
		}
	}
	stl.faces = fs;
	stl.faceCount = fs.size();
	const auto scenes = world->getObjects()->findScenes(SceneType::PolygonMeshScene);

	if (args.isBinary.getValue()) {
		STLBinaryFileWriter writer;
		return writer.write(args.filePath.getValue(), stl);
	}
	for (auto scene : scenes) {
		STLASCIIFileWriter writer;
		return writer.write(args.filePath.getValue(), stl);
	}
	return false;
}