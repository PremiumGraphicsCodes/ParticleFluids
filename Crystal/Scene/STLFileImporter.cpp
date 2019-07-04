#include "STLFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/STLASCIIFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "Scene.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Model;

STLFileImporter::STLFileImporter(SceneFactory* sceneFactory) :
	sceneFactory(sceneFactory)
{
	scene = sceneFactory->createScene("STL");
}

bool STLFileImporter::importSTLAscii(const std::experimental::filesystem::path& filePath)
{
	STLASCIIFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		scene->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
		return true;
	}
	return false;
}

bool STLFileImporter::importSTLBinary(const std::experimental::filesystem::path& filePath)
{
	STLBinaryFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		scene->addScene( sceneFactory->createPolygonMeshScene(builder.getPolygonMesh(), "Mesh") );
		return true;
	}
	return false;
}
