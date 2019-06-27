#include "STLFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/STLASCIIFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "Scene.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool STLFileImporter::importSTLAscii(const std::experimental::filesystem::path& filePath, Scene& repository)
{
	STLASCIIFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		repository.getFactory()->addPolygonMeshScene(builder.getPolygonMesh(), "STL");
		return true;
	}
	return false;
}

bool STLFileImporter::importSTLBinary(const std::experimental::filesystem::path& filePath, Scene& objects)
{
	STLBinaryFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		objects.getFactory()->addPolygonMeshScene(builder.getPolygonMesh(), "STL");
		return true;
	}
	return false;
}
