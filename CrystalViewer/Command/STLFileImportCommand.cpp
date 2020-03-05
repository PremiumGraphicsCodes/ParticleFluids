#include "STLFileImportCommand.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/TriangleMeshScene.h"

#include "../../Crystal/IO/STLAsciiFileReader.h"
#include "../../Crystal/IO/STLBinaryFileReader.h"

#include "Public/STLFileImportLabels.h"


using namespace Crystal::IO;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileImportCommand::Args::Args() :
	filePath(STLFileImportLabels::FilePathLabel, "")
{
	add(&filePath);
}

STLFileImportCommand::Results::Results() :
	newId(STLFileImportLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string STLFileImportCommand::getName()
{
	return STLFileImportLabels::CommandNameLabel;
}

bool STLFileImportCommand::execute(Crystal::Scene::World* scene)
{
	//if (!args.isBinary.getValue()) {
	//	STLASCIIFileReader reader;
	//	if (reader.read(args.filePath.getValue())) {
	//		/*
	//		PolygonMeshBuilder builder;
	//		const auto& stl = reader.getSTL();
	//		scene->getSceneFactory()->createPolygonMeshScene()
	//		scene->addScene( )
	//		builder.add(stl.)
	//		scene->addScene()
	//		TriangleMesh mesh(stl.faces);
	//		builder.add(mesh);
	//		parent->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
	//		*/
	//	}
	//}
	//else {
	//	STLBinaryFileReader reader;
	//	if (reader.read(args.filePath.getValue())) {
	//		PolygonMeshBuilder builder;
	//		const auto& stl = reader.getSTL();
	//		/*
	//		TriangleMesh mesh(stl.faces);
	//		builder.add(mesh);
	//		parent->addScene(sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh"));
	//		*/
	//	}
	//}
	//return true;
	return false;
}