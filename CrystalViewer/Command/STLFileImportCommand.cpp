#include "STLFileImportCommand.h"

#include "../../Crystal/Scene/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/TriangleMeshScene.h"

#include "../../Crystal/IO/STLAsciiFileReader.h"
#include "../../Crystal/IO/STLBinaryFileReader.h"

#include "Public/FileImportLabels.h"


using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileImportCommand::Args::Args() :
	filePath(FileImportLabels::FilePathLabel, ""),
	isBinary(FileImportLabels::IsBinaryLabel, false)
{
	add(&filePath);
	add(&isBinary);
}

STLFileImportCommand::Results::Results() :
	isOk(FileImportLabels::IsOkLabel, false)
{
	add(&isOk);
}

std::string STLFileImportCommand::getName()
{
	return FileImportLabels::FileImportCommandLabel;
}

void STLFileImportCommand::execute(Crystal::Scene::World* scene)
{
	if (!args.isBinary.getValue()) {
		STLASCIIFileReader reader;
		if (reader.read(args.filePath.getValue())) {
			PolygonMeshBuilder builder;
			const auto& stl = reader.getSTL();
			/*
			TriangleMesh mesh(stl.faces);
			builder.add(mesh);
			parent->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
			*/
		}
	}
	else {
		STLBinaryFileReader reader;
		if (reader.read(args.filePath.getValue())) {
			PolygonMeshBuilder builder;
			const auto& stl = reader.getSTL();
			/*
			TriangleMesh mesh(stl.faces);
			builder.add(mesh);
			parent->addScene(sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh"));
			*/
		}
	}
}