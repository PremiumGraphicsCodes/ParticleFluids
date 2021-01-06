#include "VDBVolumeMenu.h"

#include "VDBVolumeView.h"
#include "VolumeToMeshView.h"
#include "VolumeToPSView.h"

#include "../../CrystalViewer/AppBase/imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

VDBVolumeMenu::VDBVolumeMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}


void VDBVolumeMenu::onShow()
{
	auto world = getWorld();

	if (ImGui::BeginMenu("VDBVolume")) {
		if (ImGui::MenuItem("VolumeBox")) {
			control->setWindow(new VDBVolumeView("VDBVolume", world, getCanvas()));
		}
		if (ImGui::MenuItem("VolumeToMesh")) {
			control->setWindow(new VolumeToMeshView("VolumeToMesh", world, getCanvas()));
		}
		if (ImGui::MenuItem("VolumeToPS")) {
			control->setWindow(new VolumeToPSView("VolumeToPS", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
}