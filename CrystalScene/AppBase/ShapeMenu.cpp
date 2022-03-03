#include "imgui.h"

#include "ShapeMenu.h"
#include "Canvas.h"
#include "ControlPanel.h"

#include "PSBoxView.h"
#include "PSConeView.h"
#include "PSCylinderView.h"
#include "PSSphereView.h"
#include "PSTorusView.h"

#include "WFBoxView.h"
#include "WFCircleView.h"
#include "WFConeView.h"
#include "WFCylinderView.h"
#include "WFSphereView.h"
#include "WFEllipsoidView.h"
#include "WFTorusView.h"

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereView.h"
#include "PMConeView.h"

#include "TMBoxView.h"
#include "TMSphereView.h"

#include "VolSphereView.h"
#include "VoxelSphereView.h"

#include "SolidBoxView.h"

#include "ScaleView.h"
#include "TranslateView.h"
#include "TransformView.h"
#include "RotateView.h"

#include "DeleteView.h"
#include "IMenuItem.h"

#include "../Scene/World.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PSGenerationMenu::PSGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add( new MenuItem("PSSphere", [world, canvas, control] {
		control->setWindow(new PSSphereView("PSSphere", world, canvas));
	}));

	add(new MenuItem("PSBox", [world, canvas, control] {
		control->setWindow(new PSBoxView("PSBox", world, canvas));
	}));

	add( new MenuItem("PSCone", [world, canvas, control] {
		control->setWindow(new PSConeView("PSCone", world, canvas));
	}));

	add( new MenuItem("PSCylinder", [world, canvas, control] {
		control->setWindow(new PSCylinderView("PSCylinder", world, canvas));
	}));

	add( new MenuItem("PSTorus", [world, canvas, control] {
		control->setWindow(new PSTorusView("PSTorus", world, canvas));
	}));
}

WFGenerationMenu::WFGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add( new MenuItem("WFCircle", [world, canvas, control] {
		control->setWindow(new WFCircleView("WFCircle", world, canvas));
	}));

	add( new MenuItem("WFBox", [world, canvas, control] {
		control->setWindow(new WFBoxView("WFBox", world, canvas));
	}));

	add( new MenuItem("WFCone", [world, canvas, control] {
		control->setWindow(new WFBoxView("WFCone", world, canvas));
	}));

	add( new MenuItem("WFCylinder", [world, canvas, control] {
		control->setWindow(new WFCylinderView("WFCylinder", world, canvas));
	}));

	add( new MenuItem("WFSphere", [world, canvas, control] {
		control->setWindow( new WFSphereView("WFSphere", world, canvas));
	}));

	add( new MenuItem("WFEllipsoid", [world, canvas, control] {
		control->setWindow( new WFEllipsoidView("WFEllipsoid", world, canvas));
	}));

	add( new MenuItem("WFTorus", [world, canvas, control] {
		control->setWindow( new WFTorusView("WFTorus", world, canvas));
	}));
}

PMGenerationMenu::PMGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new MenuItem("PMBox", [world, canvas, control] {
		control->setWindow(new PMBoxView("PMBox", world, canvas));
	}));
	add(new MenuItem("PMQuad", [world, canvas, control] {
		control->setWindow(new PMQuadView("PMQuad", world, canvas));
	}));
	add(new MenuItem("PMSphere", [world, canvas, control] {
		control->setWindow(new PMSphereView("PMSphere", world, canvas));
	}));
	add(new MenuItem("PMCone", [world, canvas, control] {
		control->setWindow(new PMConeView("PMCone", world, canvas));
	}));
}

TMGenerationMenu::TMGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new MenuItem("TMBox", [world, canvas, control] {
		control->setWindow(new TMBoxView("TMBox", world, canvas));
	}));
	//control->setWindow(new PMQuadView("PMQuad", world, canvas));
	add(new MenuItem("TMSphere", [world, canvas, control] {
		control->setWindow(new TMSphereView("TMSphere", world, canvas));
	}));
	//control->setWindow(new PMConeView("PMCone", world, canvas));
}

VolGenerationMenu::VolGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new MenuItem("VolSphere", [world, canvas, control] {
		control->setWindow( new VolSphereView("VolSphere", world, canvas));
	}));
}

VoxelGenerationMenu::VoxelGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void VoxelGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("VoxelSphere")) {
			control->setWindow(new VoxelSphereView("VoxelSphere", world, canvas));
		}
		ImGui::EndMenu();
	}
}

SolidGenerationMenu::SolidGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{
}

void SolidGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("SolidBox")) {
			control->setWindow(new SolidBoxView("SolidBox", world, canvas));
		}
		ImGui::EndMenu();
	}
}

TransformMenu::TransformMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void TransformMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Scale")) {
			control->setWindow(new ScaleView("Scale", world, canvas));
		}
		if (ImGui::MenuItem("Translate")) {
			control->setWindow(new TranslateView("Translate", world, canvas));
		}
		if (ImGui::MenuItem("Rotate")) {
			control->setWindow(new RotateView("Rotate", world, canvas));
		}
		if (ImGui::MenuItem("Transform")) {
			control->setWindow(new TransformView("Transform", world, canvas));
		}
		ImGui::EndMenu();
	}
}

ShapeMenu::ShapeMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control),
	particleSystemMenu("ParticleSystem", world, canvas, control),
	wireFrameMenu("WireFrame", world, canvas, control),
	polygonMeshMenu("PolygonMesh", world, canvas, control),
	triangleMeshMenu("TriangleMesh", world, canvas, control),
	volMenu("Volume", world, canvas, control),
	voxelMenu("Voxel", world, canvas, control),
	solidMenu("Solid", world, canvas, control),
	transformMenu("Transform", world, canvas, control)
{}

void ShapeMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		particleSystemMenu.show();
		wireFrameMenu.show();
		polygonMeshMenu.show();
		triangleMeshMenu.show();
		volMenu.show();
		voxelMenu.show();
		solidMenu.show();
		transformMenu.show();

		if (ImGui::BeginMenu("Global")) {
			if (ImGui::MenuItem("Delete")) {
				control->setWindow(new DeleteView("Delete", world, canvas));
			}
			ImGui::EndMenu();

		}

		ImGui::EndMenu();
	}
}
