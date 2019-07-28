#include "ParticleSystemPanel.h"
#include "imgui.h"
#include "../Math/Torus3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

#include "PSBoxButton.h"
#include "PSSphereButton.h"
#include "PSCylinderButton.h"
#include "PSConeButton.h"
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
	control(control)
{
	add( new PSSphereButton(repository, canvas) );
	add( new PSCylinderButton(repository, canvas) );
	add( new PSConeButton(repository, canvas) );
	add( new PSTorusButton(repository, canvas) );
}

void ParticleSystemPanel::show()
{
	if (ImGui::Button("PSBox")) {
		control->clear();
		control->add(new PSBoxView(getRepository(), canvas));
	}
}