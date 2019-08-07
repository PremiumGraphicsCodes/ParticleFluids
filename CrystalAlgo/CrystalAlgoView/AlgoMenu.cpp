#include "AlgoMenu.h"

#include "IntersectionView.h"
#include "BooleanView.h"
#include "SpaceHashView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertView.h"
#include "OctreeView.h"
#include "SpaceHashView.h"

#include "../../Crystal/AppBase/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

AlgoMenu::AlgoMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void AlgoMenu::show()
{
	if (ImGui::BeginMenu("Algo")) {
		if (ImGui::MenuItem("Boolean")) {
			control->setWindow(new BooleanView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("SpaceHash")) {
			control->setWindow(new SpaceHashView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("Octree")) {
			control->setWindow(new OctreeView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("Intersection")) {
			control->setWindow(new IntersectionView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("Volume")) {
			control->setWindow(new VolumeView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("VolumeConvert")) {
			control->setWindow(new VolumeConvertView(getModel(), getCanvas()));
		}
		if (ImGui::MenuItem("MarchingCubes")) {
			control->setWindow(new MarchingCubesView(getModel(), getCanvas()));
		}
		ImGui::EndMenu();
	}
}
