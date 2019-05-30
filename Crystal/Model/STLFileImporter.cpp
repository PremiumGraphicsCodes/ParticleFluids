#include "STLFileImporter.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/STLASCIIFileReader.h"
#include "../IO/STLBinaryFileReader.h"
#include "ObjectRepository.h"

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool STLFileImporter::importSTLAscii(const std::experimental::filesystem::path& filePath, ObjectRepository& repository)
{
	STLASCIIFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		builder.build();
		repository.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "STL");
		return true;
	}
	return false;
}

bool STLFileImporter::importSTLBinary(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	STLBinaryFileReader reader;
	if (reader.read(filePath)) {
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		TriangleMesh mesh(stl.faces);
		builder.add(mesh);
		builder.build();
		objects.getPolygonMeshes()->addObject(builder.getPolygonMesh(), 0, "STL");
		return true;
	}
	return false;
}
