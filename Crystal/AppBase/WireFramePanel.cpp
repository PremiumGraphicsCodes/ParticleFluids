#include "WireFramePanel.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IPopupButton.h"

#include "WFBoxButton.h"
#include "WFSphereButton.h"

#include "../Math/Cone3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class WFCylinderButton : public IPopupButton
	{
	public:
		WFCylinderButton(Repository* model, Canvas* canvas) :
			IPopupButton("Cylinder", model, canvas),
			unum(12),
			vnum(12)
		{
		}

		void onShow() override
		{
			ImGui::InputInt("UNum", &unum);
			ImGui::InputInt("VNum", &vnum);
			ImGui::InputFloat3("Center", &center[0]);
			ImGui::InputDouble("Radius", &radius);
			ImGui::InputDouble("Height", &radius);
			ImGui::ColorPicker4("Color", &color[0]);
		}

		void onOk() override
		{
			const Cylinder3d sphere(radius, height, center);
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
		double radius = 1.0;
		double height = 1.0;
		glm::vec4 color;
	};


	class WFConeButton : public IPopupButton
	{
	public:
		WFConeButton(Repository* model, Canvas* canvas) :
			IPopupButton("Cone", model, canvas),
			unum(12),
			vnum(12)
		{
		}

		void onShow() override
		{
			ImGui::InputInt("UNum", &unum);
			ImGui::InputInt("VNum", &vnum);
			ImGui::InputFloat3("Center", &center[0]);
			ImGui::InputDouble("Radius", &radius);
			ImGui::InputDouble("Height", &height);
			ImGui::ColorPicker4("Color", &color[0]);
		}

		void onOk() override
		{
			const Cone3d cone(center, radius, height);
			Crystal::Shape::WireFrameBuilder builder;
			builder.build(cone, unum, vnum);
			getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Cone");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		int unum;
		int vnum;
		Vector3df center = { 0.0, 0.0, 0.0 };
		double radius = 1.0;
		double height = 1.0;
		glm::vec4 color;
	};
}

WireFramePanel::WireFramePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new WFBoxButton(model, canvas) );
	add( new WFSphereButton(model, canvas) );
	add( new WFCylinderButton(model, canvas) );
	add( new WFConeButton(model, canvas) );
}
