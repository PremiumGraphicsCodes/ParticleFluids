#include "AppearancePanel.h"
#include "../ThirdParty/imgui-1.51/imgui.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"

#include <cereal/cereal.hpp>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void AppearancePanel::show()
{
	ImGui::Begin("Appearance");
	if (ImGui::Button("Light")) {
		ImGui::OpenPopup("Light");
	}
	if (ImGui::BeginPopup("Light")) {
		static glm::vec4 ambient = { 0,0,0,0 };
		static glm::vec4 diffuse = { 0,0,0,0 };
		static glm::vec4 specular = { 0,0,0,0 };
		ImGui::ColorPicker3("Ambient", &ambient[0]);
		ImGui::ColorPicker3("Diffuse", &diffuse[0]);
		ImGui::ColorPicker3("Specular", &specular[0]);
		if (ImGui::Button("OK")) {
			auto l = new PointLight();
			l->setAmbient(ambient);
			l->setDiffuse(diffuse);
			l->setSpecular(specular);
			model->getLights()->add(l);
			canvas->setViewModel(model->toViewModel());
			canvas->fitCamera(model->getBoundingBox());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	ImGui::End();
}