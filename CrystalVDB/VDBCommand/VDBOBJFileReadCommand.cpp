#include "VDBOBJFileReadCommand.h"

#include "../VDBConverter/OBJFileReader.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VDBOBJFileWriteLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBOBJFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

VDBOBJFileReadCommand::Results::Results() :
	vdbMeshId(::VDBMeshIdLabel, {})
{
}

VDBOBJFileReadCommand::VDBOBJFileReadCommand() :
	ICommand(&args, &results)
{}

std::string VDBOBJFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBOBJFileReadCommand::execute(World* world)
{
	/*
	auto mesh = world->getScenes()->findSceneById<VDBPolygonMesh*>(args.vdbMeshId.getValue());
	if (mesh == nullptr) {
		return false;
	}

	OBJFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), *mesh);

	return isOk;
	*/
	return false;
}
