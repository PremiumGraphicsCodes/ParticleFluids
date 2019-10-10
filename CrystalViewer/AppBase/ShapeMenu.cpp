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

using namespace Crystal::UI;

void ShapeMenu::onShow()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::BeginMenu("ParticleSystem")) {
			if (ImGui::MenuItem("PSSphere")) {
				control->setWindow(new PSSphereView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PSBox")) {
				control->setWindow(new PSBoxView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PSCone")) {
				control->setWindow(new PSConeView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PSCylinder")) {
				control->setWindow(new PSCylinderView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PSTorus")) {
				control->setWindow(new PSTorusView(getModel(), canvas));
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("WireFrame")) {
			if (ImGui::MenuItem("WFBox")) {
				control->setWindow(new WFBoxView(getModel(), canvas));
			}
			if (ImGui::MenuItem("WFCone")) {
				control->setWindow(new WFConeView(getModel(), canvas));
			}
			if (ImGui::MenuItem("WFCylinder")) {
				control->setWindow(new WFCylinderView(getModel(), canvas));
			}
			if (ImGui::MenuItem("WFSphere")) {
				control->setWindow(new WFSphereView(getModel(), canvas));
			}
			if (ImGui::MenuItem("WFTorus")) {
				control->setWindow(new WFTorusView(getModel(), canvas));
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("PolygonMesh")) {
			if (ImGui::MenuItem("PMBox")) {
				control->setWindow(new PMBoxView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PMQuad")) {
				control->setWindow(new PMQuadView(getModel(), canvas));
			}
			if (ImGui::MenuItem("PMSphere")) {
				control->setWindow(new PMSphereView(getModel(), canvas));
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Transform")) {
			if (ImGui::MenuItem("Scale")) {
				control->setWindow(new ScaleView("Scale", getModel(), canvas));
			}
			if (ImGui::MenuItem("Translate")) {
				control->setWindow(new TranslateView("Translate", getModel(), canvas));
			}
			if (ImGui::MenuItem("Rotate")) {
				control->setWindow(new RotateView("Rotate", getModel(), canvas));
			}
			if (ImGui::MenuItem("Transform")) {
				control->setWindow(new TransformView("Transform", getModel(), canvas));
			}

			ImGui::EndMenu();
		}


		ImGui::EndMenu();
	}
}
