#include "VDBMeshMenu.h"

#include "VDBPMBoxView.h"
#include "MeshToVolumeView.h"
#include "OBJFileImportView.h"
#include "OBJFileExportView.h"

#include "VDBVolumeView.h"
#include "VolumeToMeshView.h"
#include "VolumeToPSView.h"

#include "CrystalScene/AppBase/imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

VDBMeshMenu::VDBMeshMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}


void VDBMeshMenu::onShow()
{
	auto world = getWorld();

	if (ImGui::BeginMenu("VDBMesh")) {
		if (ImGui::MenuItem("PMBox")) {
			control->setWindow(new VDBPMBoxView("PMBox", world, getCanvas()));
		}
		if (ImGui::MenuItem("MeshToVolume")) {
			control->setWindow(new MeshToVolumeView("MeshToVolume", world, getCanvas()));
		}
		if (ImGui::MenuItem("OBJImport")) {
			control->setWindow(new OBJFileImportView("OBJImport", world, getCanvas()));
		}
		if (ImGui::MenuItem("OBJExport")) {
			control->setWindow(new OBJFileExportView("OBJExport", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
}