#include "PolygonMeshCreateByVolumeCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshBuilder.h"

//#include "Public/PolygonMeshCreateBySurfaceLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateByVolumeCommand::Args::Args() :
	volume("Volume", nullptr),
	uDivNum("UDiv", 24),
	vDivNum("VDiv", 24),
	wDivNum("WDiv", 24),
	name("Name", std::string(""))
{
	add(&volume);
	add(&uDivNum);
	add(&vDivNum);
	add(&wDivNum);
	add(&name);
}

PolygonMeshCreateByVolumeCommand::Results::Results() :
	newId("NewId", -1)
{
	add(&newId);
}

std::string PolygonMeshCreateByVolumeCommand::getName()
{
	return "PolygonMeshCreateByVolume";
}

void PolygonMeshCreateByVolumeCommand::execute(World* scene)
{
	PolygonMeshBuilder builder;
	auto volume = args.volume.getValue();
	const auto uNum = args.uDivNum.getValue();
	const auto vNum = args.vDivNum.getValue();
	const auto wNum = args.wDivNum.getValue();
	builder.add(*volume, uNum, vNum, wNum);

	auto shape = scene->getObjectFactory()->createPolygonMeshScene(builder.build(), args.name.getValue());
	scene->getObjects()->addScene(shape);

	const auto newId = shape->getId();

	results.newId.setValue(newId);
}