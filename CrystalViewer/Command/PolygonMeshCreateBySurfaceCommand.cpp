#include "PolygonMeshCreateBySurfaceCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshBuilder.h"

#include "Public/PolygonMeshCreateBySurfaceLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateBySurfaceCommand::Args::Args() :
	surface(PolygonMeshCreateBySurfaceLabels::SurfaceLabel, nullptr),
	uDivNum(PolygonMeshCreateBySurfaceLabels::UDivLabel, 24),
	vDivNum(PolygonMeshCreateBySurfaceLabels::VDivLabel, 24),
	name(PolygonMeshCreateBySurfaceLabels::NameLabel, std::string(""))
{
	add(&surface);
	add(&uDivNum);
	add(&vDivNum);
	add(&name);
}

PolygonMeshCreateBySurfaceCommand::Results::Results() :
	newId(PolygonMeshCreateBySurfaceLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string PolygonMeshCreateBySurfaceCommand::getName()
{
	return PolygonMeshCreateBySurfaceLabels::CommandNameLabel;
}

void PolygonMeshCreateBySurfaceCommand::execute(World* scene)
{
	PolygonMeshBuilder builder;
	auto surface = args.surface.getValue();
	const auto uNum = args.uDivNum.getValue();
	const auto vNum = args.vDivNum.getValue();
	builder.add(*surface, uNum, vNum);

	auto shape = scene->getObjectFactory()->createPolygonMeshScene(builder.build(), args.name.getValue());
	scene->getObjects()->addScene(shape);

	const auto newId = shape->getId();

	results.newId.setValue(newId);
}