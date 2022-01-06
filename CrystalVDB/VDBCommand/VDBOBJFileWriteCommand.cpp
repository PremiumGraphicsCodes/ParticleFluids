#include "VDBOBJFileWriteCommand.h"

#include "Crystal/IO/OBJFileWriter.h"
#include "CrystalScene/Command/Public/PublicLabel.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBOBJFileWrite";
	PublicLabel VDBMeshIdLabel = "VDBMeshId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBOBJFileWriteCommand::Args::Args() :
	vdbMeshId(::VDBMeshIdLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&vdbMeshId);
	add(&filePath);
}

VDBOBJFileWriteCommand::Results::Results()
{
}

VDBOBJFileWriteCommand::VDBOBJFileWriteCommand() :
	ICommand(&args, &results)
{}

std::string VDBOBJFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBOBJFileWriteCommand::execute(World* world)
{
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMeshScene*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

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
		f.positionIndices = { t.indices[0] +1, t.indices[1] +1, t.indices[2]+1 };
		f.normalIndices = { normalIndex, normalIndex, normalIndex };
		f.texCoordIndices = { 0,0,0 };
		normalIndex++;
		group.faces.push_back(f);
	}

	for (const auto& t : quads) {
		Crystal::IO::OBJFace f;
		f.positionIndices = { t.indices[0]+1, t.indices[1]+1, t.indices[2]+1, t.indices[3]+1 };
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