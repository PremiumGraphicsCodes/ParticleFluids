#include "VDBSTLFileWriteCommand.h"

#include "Crystal/IO/STLBinaryFileWriter.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSTLFileWrite";
	PublicLabel VDBMeshIdLabel = "VDBMeshId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSTLFileWriteCommand::Args::Args() :
	vdbMeshId(::VDBMeshIdLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&vdbMeshId);
	add(&filePath);
}

VDBSTLFileWriteCommand::Results::Results()
{
}

VDBSTLFileWriteCommand::VDBSTLFileWriteCommand() :
	ICommand(&args, &results)
{}

std::string VDBSTLFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSTLFileWriteCommand::execute(World* world)
{
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMeshScene*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

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

	Crystal::IO::STLBinaryFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), stl);
	return isOk;
}