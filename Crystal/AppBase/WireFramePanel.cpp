#include "WireFramePanel.h"
#include "imgui.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IPopupButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class BoxButton : public IPopupButton
	{
	public :
		BoxButton(Model* model, Canvas* canvas) :
			IPopupButton("Box", model, canvas)
		{

		}

		void onShow() override
		{
			ImGui::InputFloat3("Min", &min[0]);
			ImGui::InputFloat3("Max", &max[0]);
			ImGui::ColorPicker4("Color", &color[0]);
		}

		void onOk() override
		{
			const Box3d box(min, max);
			Crystal::Shape::WireFrameBuilder builder;
			builder.build(box);
			getModel()->getObjects()->addWireFrame(builder.getWireFrame(), color);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 min = { -1.0f, -1.0f, -1.0f };
		glm::vec3 max = { 1.0f, 1.0f, 1.0f };
		glm::vec4 color;
	};

	BoxButton* boxButton = nullptr;
}

void WireFramePanel::show()
{
	ImGui::Begin("WireFrame");

	boxButton->show();

	if (ImGui::Button("Sphere")) {
		ImGui::OpenPopup("Sphere");
	}
	if (ImGui::BeginPopup("Sphere")) {
		static glm::vec3 center = { 0.0f, 0.0f, 0.0f };
		ImGui::InputFloat3("Center", &center[0]);
		static float radius = 1.0;
		ImGui::InputFloat("Radius", &radius);
		static glm::vec4 color;
		ImGui::ColorPicker4("Color", &color[0]);

		if (ImGui::Button("OK")) {
			Sphere3d sphere(center, radius);
			Crystal::Shape::WireFrameBuilder builder;
			builder.build(sphere);
			model->getObjects()->addWireFrame(builder.getWireFrame(), color);
			canvas->setViewModel(model->toViewModel());
			canvas->fitCamera(model->getBoundingBox());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::End();
}

WireFramePanel::WireFramePanel(Model* model, Canvas* canvas) :
	IPanel(model, canvas)
{
	::boxButton = new BoxButton(model, canvas);
}
