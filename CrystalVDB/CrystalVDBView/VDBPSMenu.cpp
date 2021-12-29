#include "VDBPSMenu.h"

#include "CrystalScene/Scene/World.h"
#include "CrystalScene/AppBase/imgui.h"

#include "VDBPSBoxView.h"
#include "PSToVolumeView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

VDBPSMenu::VDBPSMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void VDBPSMenu::onShow()
{
	auto world = getWorld();

	if (ImGui::BeginMenu("VDBPS")) {
		if (ImGui::MenuItem("PSBox")) {
			control->setWindow(new VDBPSBox("PSBox", world, getCanvas()));
		}
		if (ImGui::MenuItem("PSToMesh")) {
			control->setWindow(new PSToVolumeView("PSToVolume", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
}
