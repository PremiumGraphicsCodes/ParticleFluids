#include "PMSphereView.h"

#include "../../Crystal/Scene/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../Command/Command.h"
#include "../Command/Public/PolygonMeshCreateBySurfaceLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMSphereView::PMSphereView(World* model, Canvas* canvas) :
	IOkCancelView("PMSphere", model, canvas),
	sphere("Sphere"),
	unum("UNum", 36),
	vnum("VNum", 36),
	name("Name", "PMSphere")
{
	add(&sphere);
	add(&unum);
	add(&vnum);
	add(&name);
}

void PMSphereView::onOk()
{
	std::shared_ptr<ISurface3d> surface = std::make_shared<Sphere3d>(sphere.getValue());

	Command::Command command;
	command.create(PolygonMeshCreateBySurfaceLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateBySurfaceLabels::SurfaceLabel, surface);
	command.setArg(PolygonMeshCreateBySurfaceLabels::UDivLabel, unum.getValue());
	command.setArg(PolygonMeshCreateBySurfaceLabels::VDivLabel, vnum.getValue());
	command.setArg(PolygonMeshCreateBySurfaceLabels::NameLabel, name.getValue());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	getWorld()->updateViewModel();
}
