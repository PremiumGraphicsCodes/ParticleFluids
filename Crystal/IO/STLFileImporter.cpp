#include "STLFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../Scene/PolygonMeshScene.h"
#include "../IO/STLASCIIFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "../Scene/Scene.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;

STLFileImporter::STLFileImporter(SceneFactory* sceneFactory) :
	sceneFactory(sceneFactory)
{
}

bool STLFileImporter::importSTLAscii(const std::experimental::filesystem::path& filePath, IScene* parent)
{
	STLASCIIFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		parent->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
		return true;
	}
	return false;
}

bool STLFileImporter::importSTLBinary(const std::experimental::filesystem::path& filePath, IScene* parent)
{
	STLBinaryFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		parent->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
		return true;
	}
	return false;
}
