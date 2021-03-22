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
#include "WFTorusView.h"

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereView.h"
#include "PMConeView.h"

#include "VolSphereView.h"

#include "SolidBoxView.h"

#include "ScaleView.h"
#include "TranslateView.h"
#include "TransformView.h"
#include "RotateView.h"

#include "DeleteView.h"

#include "../../Crystal/Scene/World.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PSGenerationMenu::PSGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void PSGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("PSSphere")) {
			control->setWindow(new PSSphereView("PSSphere", world, canvas));
		}
		if (ImGui::MenuItem("PSBox")) {
			control->setWindow(new PSBoxView("PSBox", world, canvas));
		}
		if (ImGui::MenuItem("PSCone")) {
			control->setWindow(new PSConeView("PSCone", world, canvas));
		}
		if (ImGui::MenuItem("PSCylinder")) {
			control->setWindow(new PSCylinderView("PSCylinder", world, canvas));
		}
		if (ImGui::MenuItem("PSTorus")) {
			control->setWindow(new PSTorusView("PSTorus", world, canvas));
		}
		ImGui::EndMenu();
	}
}

WFGenerationMenu::WFGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void WFGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("WFCircle")) {
			control->setWindow(new WFCircleView("WFCircle", world, canvas));
		}
		if (ImGui::MenuItem("WFBox")) {
			control->setWindow(new WFBoxView("WFBox", world, canvas));
		}
		if (ImGui::MenuItem("WFCone")) {
			control->setWindow(new WFConeView("WFCone", world, canvas));
		}
		if (ImGui::MenuItem("WFCylinder")) {
			control->setWindow(new WFCylinderView("WFCylinder", world, canvas));
		}
		if (ImGui::MenuItem("WFSphere")) {
			control->setWindow(new WFSphereView("WFSphere", world, canvas));
		}
		if (ImGui::MenuItem("WFTorus")) {
			control->setWindow(new WFTorusView("WFTorus", world, canvas));
		}
		ImGui::EndMenu();
	}
}

PMGenerationMenu::PMGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void PMGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("PMBox")) {
			control->setWindow(new PMBoxView("PMBox", world, canvas));
		}
		if (ImGui::MenuItem("PMQuad")) {
			control->setWindow(new PMQuadView("PMQuad", world, canvas));
		}
		if (ImGui::MenuItem("PMSphere")) {
			control->setWindow(new PMSphereView("PMSphere", world, canvas));
		}
		if (ImGui::MenuItem("PMCone")) {
			control->setWindow(new PMConeView("PMCone", world, canvas));
		}
		ImGui::EndMenu();
	}
}

VolGenerationMenu::VolGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{}

void VolGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("VolSphere")) {
			control->setWindow(new VolSphereView("VolSphere", world, canvas));
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
	volMenu("Volume", world, canvas, control),
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
		volMenu.show();
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
