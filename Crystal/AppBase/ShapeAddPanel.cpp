#include "ShapeAddPanel.h"
#include "imgui.h"
#include "../Math/Torus3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

#include "PSBoxView.h"
#include "PSSphereView.h"
#include "PSCylinderView.h"
#include "PSConeView.h"
#include "PSTorusView.h"

#include "WFBoxView.h"
#include "WFConeView.h"

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereView.h"

#include "ControlPanel.h"

#include "IPopupButton.h"
#include "Button.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ShapeAddPanel::ShapeAddPanel(const std::string& name, Repository* repository, Canvas* canvas, ControlPanel* control) :
	IPanel(name, repository, canvas),
	control(control),
	psBox("PSBox"),
	psCone("PSCone"),
	psCylinder("PSCylinder"),
	psSphere("PSSphere"),
	psTorus("PSTorus"),
	wfBox("WFBox"),
	wfCone("WFCone"),
	pmBox("PMBox"),
	pmQuad("PMQuad"),
	pmSphere("PMSphere")
{
	psBox.setFunction
	(
		[=](){ control->setWindow(new PSBoxView(getRepository(), canvas)); }
	);
	psCone.setFunction
	(
		[=]() { control->setWindow(new PSConeView(getRepository(), canvas)); }
	);
	psCylinder.setFunction
	(
		[=]() { control->setWindow(new PSCylinderView(getRepository(), canvas)); }
	);
	psSphere.setFunction
	(
		[=]() {control->setWindow(new PSSphereView(getRepository(), canvas)); }
	);
	psTorus.setFunction
	(
		[=]() {control->setWindow(new PSTorusView(getRepository(), canvas)); }
	);

	wfBox.setFunction
	(
		[=]() {control->setWindow(new WFBoxView(getRepository(), canvas)); }
	);

	wfCone.setFunction
	(
		[=]() {control->setWindow(new WFConeView(getRepository(), canvas)); }
	);


	pmBox.setFunction
	(
		[=]() { control->setWindow(new PMBoxView(getRepository(), canvas)); }
	);
	pmQuad.setFunction
	(
		[=]() { control->setWindow(new PMQuadView(getRepository(), canvas)); }
	);
	pmSphere.setFunction
	(
		[=]() { control->setWindow(new PMSphereView(getRepository(), canvas)); }
	);

}

void ShapeAddPanel::show()
{
	psBox.show();
	psCone.show();
	psCylinder.show();
	psSphere.show();
	psTorus.show();

	wfBox.show();
	wfCone.show();

	pmBox.show();
	pmQuad.show();
	pmSphere.show();
}