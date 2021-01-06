#include "VDBOBJFileWriteCommand.h"

#include "../VDBConverter/OBJFileWriter.h"

#include "../../Crystal/IO/OBJFileWriter.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VDBOBJFileWriteLabels.h"

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
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMesh*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

	Crystal::IO::OBJFile obj;
	obj.positions = mesh->getVerticesf();

	const auto& triangles = mesh->getTriangles();
	for (const auto& t : triangles) {
		obj.normals.emplace_back(t.normal);
	}

	const auto& quads = mesh->getQuads();
	for (const auto& q : quads) {
		obj.normals.emplace_back(q.normal);
	}

	int normalIndex = 1;
	/*
	Crystal::IO::OBJGroup group;
	for (const auto& t : triangles) {
		Crystal::IO::OBJFace face;
		face.positionIndices = { t.indices[0], t.indices[1], t.indices[2] };
		group.faces.push_back();
	}

	for (const auto& t : quads) {
		group.faces.emplace_back(t.indices);
	}
	*/

	Crystal::IO::OBJFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), obj);
	return isOk;
}