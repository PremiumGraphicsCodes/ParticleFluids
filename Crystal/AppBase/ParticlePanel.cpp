#include "ParticlePanel.h"
#include "imgui.h"
#include "../Math/Sphere3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

#include "IPopupButton.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class WFBoxButton : public IPopupButton
	{
	public:
		WFBoxButton(Repository* model, Canvas* canvas) :
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
			getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), 100.0f, "Box");
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

	class WFSphereButton : public IPopupButton
	{
	public:
		WFSphereButton(Repository* model, Canvas* canvas) :
			IPopupButton("Sphere", model, canvas)
		{

		}

		void onShow() override
		{
			ImGui::InputFloat3("Center", &center[0]);
			ImGui::InputFloat("Radius", &radius);
			ImGui::InputFloat("Size", &size);
			ImGui::InputInt("Count", &count);
		}

		void onOk() override
		{
			const Crystal::Math::Sphere3d sphere(center, radius);
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_real_distribution<double> dist(0.0, 1.0);
			std::vector<Vector3df> positions;
			for (int i = 0; i < count; ++i) {
				const auto u = dist(mt);
				const auto v = dist(mt);
				positions.push_back(sphere.getPosition(u, v));
			}
			getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), size, "Sphere");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{
		}

	private:
		glm::vec3 center = { 0.0f, 0.0f, 0.0f };
		float radius = 1.0f;
		float size = 1.0f;

		int count = 10000;

	};
}


ParticlePanel::ParticlePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)	
{
	add( new WFBoxButton(model, canvas) );
	add( new WFSphereButton(model, canvas) );
}
