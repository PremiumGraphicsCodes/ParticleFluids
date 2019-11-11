#include "PolygonMeshCreateBySurfaceCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshBuilder.h"

#include "Public/PolygonMeshCreateBySurfaceLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateBySurfaceCommand::Args::Args() :
	surfaces(PolygonMeshCreateBySurfaceLabels::SurfacesLabel, {}),
	uDivNum("UDivNum", 24),
	vDivNum("VDivNum", 24),
	name("Name", std::string(""))
{
	add(&surfaces);
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
	const auto& surfaces = std::any_cast<std::vector<Math::ISurface3d*>>(args.surfaces.getValue());
	const auto uNum = std::any_cast<int>( args.uDivNum.getValue() );
	const auto vNum = std::any_cast<int>( args.vDivNum.getValue() );
	for (auto s : surfaces) {
		builder.add(*s, uNum, vNum);
	}

	auto shape = scene->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), args.name.getValue());
	const auto newId = shape->getId();

	results.newId.setValue(newId);
}