#include "ShapeMenu.h"
#include "imgui.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"
#include "ControlPanel.h"

#include "PSBoxView.h"
#include "PSConeView.h"
#include "PSCylinderView.h"
#include "PSSphereView.h"
#include "PSTorusView.h"

#include "WFBoxView.h"
#include "WFConeView.h"
#include "WFCylinderView.h"
#include "WFSphereView.h"
#include "WFTorusView.h"

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereView.h"

#include "ScaleView.h"
#include "TranslateView.h"
#include "TransformView.h"
#include "RotateView.h"

#include "DeleteView.h"

using namespace Crystal::UI;

void PCGenerationMenu::onShow()
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

void WFGenerationMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();

	if (ImGui::BeginMenu("WireFrame")) {
		if (ImGui::MenuItem("WFBox")) {
			control->setWindow(new WFBoxView(getWorld(), canvas));
		}
		if (ImGui::MenuItem("WFCone")) {
			control->setWindow(new WFConeView(getWorld(), canvas));
		}
		if (ImGui::MenuItem("WFCylinder")) {
			control->setWindow(new WFCylinderView(getWorld(), canvas));
		}
		if (ImGui::MenuItem("WFSphere")) {
			control->setWindow(new WFSphereView(getWorld(), canvas));
		}
		if (ImGui::MenuItem("WFTorus")) {
			control->setWindow(new WFTorusView(getWorld(), canvas));
		}
		ImGui::EndMenu();
	}
}

void ShapeMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		pointCloudMenu.show();
		wireFrameMenu.show();

		if (ImGui::BeginMenu("PolygonMesh")) {
			if (ImGui::MenuItem("PMBox")) {
				control->setWindow(new PMBoxView("PMBox", world, canvas));
			}
			if (ImGui::MenuItem("PMQuad")) {
				control->setWindow(new PMQuadView("PMQuad", world, canvas));
			}
			if (ImGui::MenuItem("PMSphere")) {
				control->setWindow(new PMSphereView("PMSphere", world, canvas));
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Transform")) {
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

		if (ImGui::BeginMenu("Global")) {
			if (ImGui::MenuItem("Delete")) {
				control->setWindow(new DeleteView("Delete", world, canvas));
			}
			ImGui::EndMenu();

		}

		ImGui::EndMenu();
	}
}
