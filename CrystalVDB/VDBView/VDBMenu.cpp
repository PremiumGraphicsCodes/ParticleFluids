#include "VDBMenu.h"

//#include "../../CrystalViewer/AppBase/"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/AppBase/imgui.h"
#include "../../CrystalViewer/AppBase/FileOpenMenu.h"
#include "../../CrystalViewer/AppBase/FileSaveMenu.h"

#include "../VDBConverter/VDBFileReader.h"
#include "../VDBConverter/VDBFileWriter.h"

#include "VDBPSBoxView.h"
#include "VDBPMBoxView.h"
#include "VDBVolumeView.h"
#include "PSToVolumeView.h"
#include "VolumeToMeshView.h"
#include "MeshToVolumeView.h"
#include "VolumeToPSView.h"
#include "OBJFileImportView.h"
#include "OBJFileExportView.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBMenu::VDBMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void VDBMenu::onShow()
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

VDBPolygonMeshMenu::VDBPolygonMeshMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}


void VDBPolygonMeshMenu::onShow()
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
	if(ImGui::BeginMenu("VDBVolume")){
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