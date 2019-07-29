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

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereButton.h"

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


	/*
		else if (ImGui::Button("PSSphere")) {
		control->clear();
		control->add(new PSSphereView(getRepository(), canvas));
	}
	*/


	//add( new PSTorusButton(repository, canvas) );
}

void ShapeAddPanel::show()
{
	psBox.show();
	psCone.show();
	psCylinder.show();
	psSphere.show();
	psTorus.show();

	pmBox.show();
	pmQuad.show();
	pmSphere.show();
}