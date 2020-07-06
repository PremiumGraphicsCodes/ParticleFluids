#include "AlgoMenu.h"

#include "IntersectionView.h"
#include "BooleanView.h"
#include "IndexedSortSearchAlgoView.h"
#include "SpaceHashView.h"
#include "CompactSpaceHash3dView.h"
#include "ZOrderSearchView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertView.h"
#include "OctreeView.h"
#include "SpaceHashView.h"
#include "UniformGrid3dView.h"

#include "../../CrystalViewer/AppBase/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

AlgoMenu::AlgoMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void AlgoMenu::onShow()
{
	if (ImGui::BeginMenu("Algo")) {
		if (ImGui::MenuItem("Boolean")) {
			control->setWindow(new BooleanView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("SpaceHash")) {
			control->setWindow(new SpaceHashView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("CompactSpaceHash")) {
			control->setWindow(new CompactSpaceHash3dView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("IndexedSortSearch")) {
			control->setWindow(new IndexedSortSearchAlgoView(getWorld(), getCanvas()));
		}
		if (ImGui::MenuItem("ZOrderSearch")) {
			control->setWindow(new ZOrderSearchView(getWorld(), getCanvas()));
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
		if (ImGui::MenuItem("UniformGrid")) {
			control->setWindow(new UniformGrid3dView(getWorld(), getCanvas()));
		}
		ImGui::EndMenu();
	}
}
