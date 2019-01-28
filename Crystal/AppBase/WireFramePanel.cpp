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

	class SphereButton : public IPopupButton
	{
	public:
		SphereButton(Model* model, Canvas* canvas) :
			IPopupButton("Sphere", model, canvas)
		{
		}

		void onShow() override
		{
			ImGui::InputFloat3("Center", &center[0]);
			ImGui::InputFloat("Radius", &radius);
			ImGui::ColorPicker4("Color", &color[0]);
		}

		void onOk() override
		{
			Sphere3d sphere(center, radius);
			Crystal::Shape::WireFrameBuilder builder;
			builder.build(sphere);
			getModel()->getObjects()->addWireFrame(builder.getWireFrame(), color);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 center = { 0.0f, 0.0f, 0.0f };
		float radius = 1.0;
		glm::vec4 color;
	};
}

void WireFramePanel::show()
{
	ImGui::Begin("WireFrame");

	for (auto c : children) {
		c->show();
	}

	ImGui::End();
}

WireFramePanel::WireFramePanel(Model* model, Canvas* canvas) :
	IPanel("WireFrame", model, canvas)
{
	add( new BoxButton(model, canvas) );
	add( new SphereButton(model, canvas) );
}
