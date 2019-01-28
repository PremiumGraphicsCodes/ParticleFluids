#include "PolygonPanel.h"
#include "../Math/Vector3d.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "../Graphics/ColorRGBA.h"
#include "imgui.h"
#include "IPopupButton.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

namespace {
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
			ImGui::InputFloat3("Radius", &radius);
			ImGui::InputInt("UNum", &unum);
			ImGui::InputInt("VNum", &vnum);
		}

		void onOk() override
		{
			PolygonMeshBuilder builder;
			const Sphere3d sphere(center, radius);
			builder.build(sphere, unum, vnum);
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			material.setDiffuse(glm::vec3(0, 1, 0));
			getModel()->getObjects()->addPolygonMesh(builder.getPolygonMesh(), material);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 center = { 0,0,0 };
		float radius = 1.0f;
		int unum = 36;
		int vnum = 36;
	};

	class BoxButton : public IPopupButton
	{
	public:
		BoxButton(Model* model, Canvas* canvas) :
			IPopupButton("Box", model, canvas)
		{
		}

		void onShow() override
		{
			ImGui::InputFloat3("Point1", &point1[0]);
			ImGui::InputFloat3("Point2", &point2[0]);
		}

		void onOk() override
		{
			PolygonMeshBuilder builder;
			const Box3d box(point1, point2);
			builder.build(box);
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			material.setSpecular(glm::vec3(0, 1, 0));
			material.setDiffuse(glm::vec3(0, 0, 1));
			getModel()->getObjects()->addPolygonMesh(builder.getPolygonMesh(), material);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 point1 = { 0,0,0 };
		glm::vec3 point2 = { 1,1,1 };
	};

	class PlaneButton : public IPopupButton
	{
	public:
		PlaneButton(Model* model, Canvas* canvas) :
			IPopupButton("Plane",model, canvas)
		{
		}

		void onShow() override
		{
		}

		void onOk()
		{
			PolygonMeshBuilder builder;
			builder.build(origin, uvec, vvec);
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			getModel()->getObjects()->addPolygonMesh(builder.getPolygonMesh(), material);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel()
		{

		}

	private:
		glm::vec3 origin = { 0, 0, 0 };
		glm::vec3 uvec = { 1, 0, 0 };
		glm::vec3 vvec = { 0, 1, 0 };
	};
}

void PolygonPanel::show()
{
	ImGui::Begin("Polygon");

	for (auto c : children) {
		c->show();
	}

	ImGui::End();
}

PolygonPanel::PolygonPanel(Model* model, Canvas* canvas) :
	IPanel("Polygon", model, canvas)
{
	add( new SphereButton(model, canvas) );
	add( new BoxButton(model, canvas) );
	add( new PlaneButton(model, canvas) );
}
