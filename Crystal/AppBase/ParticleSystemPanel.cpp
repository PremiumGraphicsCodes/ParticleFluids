#include "ParticleSystemPanel.h"
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

ParticleSystemPanel::ParticleSystemPanel(const std::string& name, Repository* repository, Canvas* canvas, ControlPanel* control) :
	IPanel(name, repository, canvas),
	control(control),
	box("PSBox"),
	cone("PSCone"),
	cylinder("PSCylinder"),
	sphere("PSSphere")
{
	box.setFunction([=]() { control->setWindow(new PSBoxView(getRepository(), canvas)); });
	cone.setFunction([=]() { control->setWindow(new PSConeView(getRepository(), canvas)); });
	cylinder.setFunction([=]() { control->setWindow(new PSCylinderView(getRepository(), canvas)); });
	sphere.setFunction([=]() {control->setWindow(new PSSphereView(getRepository(), canvas)); });
	/*
		else if (ImGui::Button("PSSphere")) {
		control->clear();
		control->add(new PSSphereView(getRepository(), canvas));
	}
	*/


	//add( new PSTorusButton(repository, canvas) );
}

void ParticleSystemPanel::show()
{
	box.show();
	cone.show();
	cylinder.show();
	sphere.show();
}