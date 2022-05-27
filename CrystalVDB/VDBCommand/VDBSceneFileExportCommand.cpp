#include "VDBSceneFileExportCommand.h"

#include "Crystal/IO/PLYFileWriter.h"
#include "Crystal/IO/PCDFileWriter.h"
#include "Crystal/IO/STLFileWriter.h"
#include "Crystal/IO/OBJFileWriter.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBScene.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;
using namespace Crystal::IO;

VDBSceneFileExportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, ""),
	vdbSceneId(::VDBSceneIdLabel, -1)
{
	add(&filePath);
	add(&fileFormat);
	add(&vdbSceneId);
}

VDBSceneFileExportCommand::Results::Results()
{
}

VDBSceneFileExportCommand::VDBSceneFileExportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileExportCommand::VDBSceneFileExportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileExportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileExportCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	const auto points = scene->getPoints();
	const auto meshes = scene->getMeshes();

	const auto format = args.fileFormat.getValue();
	if (format == FileFormat_PLY_Label) {
		for (auto p : points) {
			const auto isOk = writePLY(p);
			if (!isOk) {
				return false;
			}
		}
	}
	else if (format == FileFormat_PCD_Label) {
		for (auto p : points) {
			const auto isOk = writePCD(p);
			if (!isOk) {
				return false;
			}
		}
	}
	else if (format == FileFormat_STL_Label) {
		for (auto m : meshes) {
			const auto isOk = writeSTL(m);
			if (!isOk) {
				return false;
			}
		}
	}
	else if (format == FileFormat_OBJ_Label) {
		for (auto m : meshes) {
			const auto isOk = writeOBJ(m);
			if (!isOk) {
				return false;
			}
		}
	}
	else {
		assert(false);
		return false;
	}
	return true;
}

bool VDBSceneFileExportCommand::writePLY(VDBParticleSystemScene* vdbPoints)
{
	assert(vdbPoints != nullptr);

	const auto filePath = args.filePath.getValue();

	const auto points = vdbPoints->getPositions();
	Crystal::IO::PLYFile ply;
	for (auto p : points) {
		PLYPoint vertex;
		vertex.values.push_back(p.x);
		vertex.values.push_back(p.y);
		vertex.values.push_back(p.z);
		ply.vertices.push_back(vertex);
	}

	Crystal::IO::PLYFileWriter writer;
	const auto isOk = writer.writeBinary(filePath, ply);
	if (!isOk) {
		return false;
	}
	return true;
}

bool VDBSceneFileExportCommand::writePCD(VDBParticleSystemScene* vdbPoints)
{
	assert(vdbPoints != nullptr);

	const auto filePath = args.filePath.getValue();

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

bool VDBSceneFileExportCommand::writeSTL(VDBPolygonMeshScene* mesh)
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
	const auto isOk = writer.writeBinary(args.filePath.getValue(), stl);
	return isOk;
}

bool VDBSceneFileExportCommand::writeOBJ(VDBPolygonMeshScene* mesh)
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
	const auto isOk = writer.write(args.filePath.getValue(), obj);
	return isOk;
}