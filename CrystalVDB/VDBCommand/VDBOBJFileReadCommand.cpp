/*
#include "VDBOBJFileReadCommand.h"

#include "../VDBConverter/OBJFileReader.h"

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

	OBJFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), *mesh);

	return isOk;
}
*/