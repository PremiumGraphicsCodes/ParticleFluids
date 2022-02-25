#include "SpaceMenu.h"

#include "IntersectionView.h"
#include "IndexedSortSearchAlgoView.h"
#include "SpaceHashView.h"
#include "CompactSpaceHash3dView.h"
#include "ZOrderSearchView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertView.h"
#include "OctreeView.h"
#include "LinearOctreeView.h"
#include "DynamicOctreeView.h"
#include "SpaceHashView.h"
#include "UniformGrid3dView.h"
#include "MeshToParticleView.h"

#include "SVSphereView.h"
#include "SVBoxView.h"
#include "VoxelSphereView.h"
#include "VoxelizerView.h"
#include "ScanLineVoxelizerView.h"
#include "RayTracerView.h"

#include "CrystalScene/AppBase/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

SpaceMenu::SpaceMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void SpaceMenu::onShow()
{
	const auto world = getWorld();
	const auto canvas = getCanvas();

	if (ImGui::BeginMenu("Space")) {
		if (ImGui::MenuItem("SpaceHash")) {
			control->setWindow(new SpaceHashView("SpaceHash", world, canvas));
		}
		if (ImGui::MenuItem("CompactSpaceHash")) {
			control->setWindow(new CompactSpaceHash3dView("CompactSpaceHash", world, canvas));
		}
		if (ImGui::MenuItem("IndexedSortSearch")) {
			control->setWindow(new IndexedSortSearchAlgoView("IndexedSort", world, canvas));
		}
		if (ImGui::MenuItem("ZOrderSearch")) {
			control->setWindow(new ZOrderSearchView("ZOrderSearch", world, canvas));
		}
		if (ImGui::MenuItem("Octree")) {
			control->setWindow(new OctreeView("Octree", world, canvas));
		}
		if (ImGui::MenuItem("LinearOctree")) {
			control->setWindow(new LinearOctreeView("LinearOctree", world, canvas));
		}
		if (ImGui::MenuItem("DynamicOctree")) {
			control->setWindow(new DynamicOctreeView("DynamicOctree",world, canvas));
		}
		if (ImGui::MenuItem("Intersection")) {
			control->setWindow(new IntersectionView("Intersection", world, canvas));
		}
		if (ImGui::MenuItem("Volume")) {
			control->setWindow(new VolumeView("Volume", world, canvas));
		}
		if (ImGui::MenuItem("VolumeConvert")) {
			control->setWindow(new VolumeConvertView("VolumeConvert", world, canvas));
		}
		if (ImGui::MenuItem("MarchingCubes")) {
			control->setWindow(new MarchingCubesView("MarchingCubes", world, canvas));
		}
		if (ImGui::MenuItem("UniformGrid")) {
			control->setWindow(new UniformGrid3dView("UniformGrid", world, canvas));
		}
		if (ImGui::MenuItem("MeshToParticle")) {
			control->setWindow(new MeshToParticleView("MeshToParticle", world, canvas));
		}
		if (ImGui::MenuItem("SVSphere")) {
			control->setWindow(new SVSphereView("SVSphere", world, canvas));
		}
		if (ImGui::MenuItem("SVBox")) {
			control->setWindow(new SVBoxView("SVBox", world, canvas));
		}
		if (ImGui::MenuItem("VoxelSphere")) {
			control->setWindow(new VoxelSphereView("VoxelSphere", world, canvas));
		}
		if (ImGui::MenuItem("Voxelizer")) {
			control->setWindow(new VoxelizerView("Voxelizer", world, canvas));
		}
		if (ImGui::MenuItem("ScanLineVoxelizer")) {
			control->setWindow(new ScanLineVoxelizerView("ScanLineVoxelizer", world, canvas));
		}
		if (ImGui::MenuItem("RayTracer")) {
			control->setWindow(new RayTracerView("RayTracer", world, canvas));
		}
		ImGui::EndMenu();
	}
}
