#include "WireFramePanel.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IPopupButton.h"

#include "WFBoxButton.h"

#include "../Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {

	class WFSphereButton : public IPopupButton
	{
	public:
		WFSphereButton(Repository* model, Canvas* canvas) :
			IPopupButton("Sphere", model, canvas),
			unum(12),
			vnum(12)
		{
		}

		void onShow() override
		{
			ImGui::InputInt("UNum", &unum);
			ImGui::InputInt("VNum", &vnum);
			ImGui::InputFloat3("Center", &center[0]);
			ImGui::InputFloat("Radius", &radius);
			ImGui::ColorPicker4("Color", &color[0]);
		}

		void onOk() override
		{
			Sphere3d sphere(center, radius);
			Crystal::Shape::WireFrameBuilder builder;
			builder.build(sphere, unum, vnum);
			getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Sphere");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		int unum;
		int vnum;
		glm::vec3 center = { 0.0f, 0.0f, 0.0f };
		float radius = 1.0;
		glm::vec4 color;
	};
}

WireFramePanel::WireFramePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new WFBoxButton(model, canvas) );
	add( new WFSphereButton(model, canvas) );
}
