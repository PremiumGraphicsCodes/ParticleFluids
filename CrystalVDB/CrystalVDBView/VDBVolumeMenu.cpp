#include "VDBVolumeMenu.h"

#include "VDBVolumeView.h"
#include "VDBSphereView.h"
#include "VDBFilterView.h"
#include "VolumeToMeshView.h"
#include "VolumeToPSView.h"
#include "ToVDBVolumeView.h"

#include "CrystalScene/AppBase/imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

VDBVolumeMenu::VDBVolumeMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}


void VDBVolumeMenu::onShow()
{
	const auto world = getWorld();
	const auto canvas = getCanvas();

	if (ImGui::BeginMenu("VDBVolume")) {
		if (ImGui::MenuItem("Box")) {
			control->setWindow(new VDBVolumeView("Box", world, canvas));
		}
		if (ImGui::MenuItem("Sphere")) {
			control->setWindow(new VDBSphereView("Sphere", world, canvas));
		}
		if (ImGui::MenuItem("Filter")) {
			control->setWindow(new VDBFilterView("Filter", world, canvas));
		}
		if (ImGui::MenuItem("VolumeToMesh")) {
			control->setWindow(new VolumeToMeshView("VolumeToMesh", world, canvas));
		}
		if (ImGui::MenuItem("VolumeToPS")) {
			control->setWindow(new VolumeToPSView("VolumeToPS", world, canvas));
		}
		if (ImGui::MenuItem("ToVDBVolume")) {
			control->setWindow(new ToVDBVolumeView("ToVDBVolume", world, canvas));
		}
		ImGui::EndMenu();
	}
}