#include "ParticlePanel.h"
#include "../ThirdParty/imgui-1.51/imgui.h"
#include "../Math/Sphere3d.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"

#include "IPopupButton.h"

#include <cereal/cereal.hpp>
#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class BoxButton : public IPopupButton
	{
	public:
		BoxButton(Model* model, Canvas* canvas) :
			IPopupButton("Box", model, canvas)
		{

		}

		void onShow() override
		{
			ImGui::InputFloat3("Min", &min[0]);
			ImGui::InputFloat3("Max", &max[0]);
			ImGui::InputFloat3("Dx", &dx[0]);
		}

		void onOk() override
		{
			std::vector<Vector3df> positions;
			for (double x = min.x; x < max.x; x += dx[0]) {
				for (double y = min.y; y < max.y; y += dx[1]) {
					for (double z = min.z; z < max.z; z += dx[2]) {
						positions.push_back(Vector3df(x, y, z));
					}
				}
			}
			getModel()->getObjects()->addParticleSystem(positions, ColorRGBAf(1, 1, 1, 1), 100.0f);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 min = { -10.0f, -10.0f, -10.0f };
		glm::vec3 max = { 10.0f, 10.0f, 10.0f };
		glm::vec3 dx = { 1.0f, 1.0f, 1.0f };
	};

	BoxButton* boxButton = nullptr;
}


void ParticlePanel::show()
{
	ImGui::Begin("Particle");

	//BoxButton boxButton(model, canvas);

	if (ImGui::Button("Box")) {
		ImGui::OpenPopup("Box");
	}
	if (ImGui::BeginPopup("Box")) {
		::boxButton->onShow();
		if (ImGui::Button("OK")) {
			::boxButton->onOk();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Cancel")) {
			::boxButton->onCancel();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (ImGui::Button("Sphere")) {
		ImGui::OpenPopup("Sphere");
	}
	if (ImGui::BeginPopup("Sphere")) {
		static glm::vec3 center = { 0.0f, 0.0f, 0.0f };
		ImGui::InputFloat3("Min", &center[0]);
		static float radius = 1.0f;
		ImGui::InputFloat("Center", &radius);
		static float size = 1.0f;
		ImGui::InputFloat("Size", &size);
		static int count = 10000;
		ImGui::InputInt("Count", &count);

		if (ImGui::Button("OK")) {
			const Math::Sphere3d sphere(center, radius);
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_real_distribution<double> dist(0.0, 1.0);
			std::vector<Vector3df> positions;
			for (int i = 0; i < count; ++i) {
				const auto u = dist(mt);
				const auto v = dist(mt);
				positions.push_back( sphere.getPosition(u, v) );
			}
			model->getObjects()->addParticleSystem(positions, ColorRGBAf(1, 1, 1, 1), size);
			canvas->setViewModel(model->toViewModel());
			canvas->fitCamera(model->getBoundingBox());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}


	ImGui::End();
}

ParticlePanel::ParticlePanel(Model* model, Canvas* canvas) :
	IPanel(model, canvas)	
{
	::boxButton = new BoxButton(model, canvas);
}
