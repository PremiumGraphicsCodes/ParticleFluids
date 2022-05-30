#include "VDBFileExporter.h"

#include "Crystal/IO/PLYFileWriter.h"
#include "Crystal/IO/PCDFileWriter.h"
#include "Crystal/IO/STLFileWriter.h"
#include "Crystal/IO/OBJFileWriter.h"

#include "VDBPointsScene.h"
#include "VDBPolygonMeshScene.h"

#include <cassert>

using namespace Crystal::IO;
using namespace Crystal::VDB;

bool VDBFileExporter::writePLY(VDBPointsScene* vdbPoints, const std::string& filePath)
{
	assert(vdbPoints != nullptr);

	const auto points = vdbPoints->getPositions();
	Crystal::IO::PLYFile ply;
	for (auto p : points) {
		PLYPoint vertex;
		vertex.values.push_back((float)p.x);
		vertex.values.push_back((float)p.y);
		vertex.values.push_back((float)p.z);
		ply.vertices.push_back(vertex);
	}

	ply.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));

	Crystal::IO::PLYFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, ply);
	if (!isOk) {
		return false;
	}
	return true;
}

bool VDBFileExporter::writePCD(VDBPointsScene* vdbPoints, const std::string& filePath)
{
	assert(vdbPoints != nullptr);

	const auto points = vdbPoints->getPositions();
	Crystal::IO::PCDFile pcd;
	pcd.header.points = points.size();
	pcd.header.width = points.size();
	pcd.data.positions = points;

	Crystal::IO::PCDFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, pcd);
	if (!isOk) {
		return false;
	}
	return true;
}

bool VDBFileExporter::writeSTL(VDBPolygonMeshScene* mesh, const std::string& filePath)
{
	assert(mesh != nullptr);

	Crystal::IO::STLFile stl;

	const auto& triangles = mesh->getTriangleFaces();
	const auto vs = mesh->getVerticesf();
	for (const auto& t : triangles) {
		const auto v0 = vs[t.indices[0]];
		const auto v1 = vs[t.indices[1]];
		const auto v2 = vs[t.indices[2]];
		Crystal::IO::STLFace f;
		f.triangle = Crystal::Math::Triangle3d(v0, v1, v2);
		f.normal = t.normal;
		stl.faces.push_back(f);
	}

	const auto& quads = mesh->getQuadFaces();
	for (const auto& t : quads) {
		const auto v0 = vs[t.indices[0]];
		const auto v1 = vs[t.indices[1]];
		const auto v2 = vs[t.indices[2]];
		const auto v3 = vs[t.indices[3]];
		Crystal::IO::STLFace f1;
		f1.triangle = Crystal::Math::Triangle3d(v0, v1, v2);
		f1.normal = t.normal;
		stl.faces.push_back(f1);

		Crystal::IO::STLFace f2;
		f2.triangle = Crystal::Math::Triangle3d(v0, v2, v3);
		f2.normal = t.normal;
		stl.faces.push_back(f2);
	}
	stl.faceCount = stl.faces.size();

	Crystal::IO::STLFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, stl);
	return isOk;
}

bool VDBFileExporter::writeOBJ(VDBPolygonMeshScene* mesh, const std::string& filePath)
{
	assert(mesh != nullptr);

	Crystal::IO::OBJFile obj;
	obj.positions = mesh->getVerticesf();

	const auto& triangles = mesh->getTriangleFaces();
	for (const auto& t : triangles) {
		obj.normals.emplace_back(t.normal);
	}

	const auto& quads = mesh->getQuadFaces();
	for (const auto& t : quads) {
		obj.normals.emplace_back(t.normal);
	}

	int normalIndex = 1;
	Crystal::IO::OBJGroup group;
	for (const auto& t : triangles) {
		Crystal::IO::OBJFace f;
		f.positionIndices = { t.indices[0] + 1, t.indices[1] + 1, t.indices[2] + 1 };
		f.normalIndices = { normalIndex, normalIndex, normalIndex };
		f.texCoordIndices = { 0,0,0 };
		normalIndex++;
		group.faces.push_back(f);
	}

	for (const auto& t : quads) {
		Crystal::IO::OBJFace f;
		f.positionIndices = { t.indices[0] + 1, t.indices[1] + 1, t.indices[2] + 1, t.indices[3] + 1 };
		f.normalIndices = { normalIndex, normalIndex, normalIndex, normalIndex };
		f.texCoordIndices = { 0,0,0,0 };
		normalIndex++;
		group.faces.push_back(f);
	}
	obj.groups.emplace_back(group);

	Crystal::IO::OBJFileWriter writer;
	const auto isOk = writer.write(filePath, obj);
	return isOk;
}