#include "ShapeAddPanel.h"
#include "imgui.h"
#include "../Math/Torus3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

#include "PSBoxView.h"
#include "PSSphereView.h"
#include "PSCylinderView.h"
#include "PSConeView.h"
#include "PSTorusButton.h"
#include "ControlPanel.h"

#include "Cone3dView.h"

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
	psSphere("PSSphere")
{
	psBox.setFunction([=]() { control->setWindow(new PSBoxView(getRepository(), canvas)); });
	psCone.setFunction([=]() { control->setWindow(new PSConeView(getRepository(), canvas)); });
	psCylinder.setFunction([=]() { control->setWindow(new PSCylinderView(getRepository(), canvas)); });
	psSphere.setFunction([=]() {control->setWindow(new PSSphereView(getRepository(), canvas)); });
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
}