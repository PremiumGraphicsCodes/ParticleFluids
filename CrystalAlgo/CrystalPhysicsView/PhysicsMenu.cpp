#include "PhysicsMenu.h"

#include "FluidSimulationView.h"

/*
#include "IntersectionView.h"
#include "BooleanView.h"
#include "SpaceHashView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertView.h"
#include "OctreeView.h"
#include "SpaceHashView.h"
*/

#include "../../CrystalViewer/AppBase/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PhysicsMenu::PhysicsMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void PhysicsMenu::onShow()
{
	if (ImGui::BeginMenu("Algo")) {
		if (ImGui::MenuItem("Fluid")) {
			control->setWindow(new FluidSimulationView(getWorld(), getCanvas()));
		}
		/*
		if (ImGui::MenuItem("SpaceHash")) {
			control->setWindow(new SpaceHashView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("Octree")) {
			control->setWindow(new OctreeView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("Intersection")) {
			control->setWindow(new IntersectionView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("Volume")) {
			control->setWindow(new VolumeView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("VolumeConvert")) {
			control->setWindow(new VolumeConvertView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("MarchingCubes")) {
			control->setWindow(new MarchingCubesView(getWorld(), getCanvas()));
		}
		*/
		ImGui::EndMenu();
	}
}
